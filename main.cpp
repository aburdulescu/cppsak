#include <clang-c/Index.h>

#include <cstring>
#include <functional>
#include <iostream>
#include <string_view>
#include <vector>

struct Entry {
  std::string name;
  std::vector<std::string> literals;
};

static int FindEntry(const std::vector<Entry>& entries, const char* name) {
  for (size_t i = 0; i < entries.size(); ++i)
    if (std::strcmp(entries[i].name.c_str(), name) == 0) return i;
  return -1;
}

std::vector<Entry> entries;

std::vector<const char*> wanted;

static bool WantedEnum(std::vector<const char*> wanted, const char* name) {
  for (auto e : wanted)
    if (std::strcmp(e, name) == 0) return true;
  return false;
}

static CXChildVisitResult visitor(CXCursor cursor, CXCursor parent,
                                  CXClientData client_data) {
  (void)client_data;

  auto kind = clang_getCursorKind(cursor);

  // {
  //   auto spelling = clang_getCursorSpelling(cursor);
  //   auto kindSpelling = clang_getCursorKindSpelling(kind);
  //   std::printf("%s, %s, %d\n", clang_getCString(spelling),
  //               clang_getCString(kindSpelling), kind);
  //   clang_disposeString(spelling);
  //   clang_disposeString(kindSpelling);
  // }

  switch (kind) {
    case CXCursorKind::CXCursor_EnumDecl: {
      if (clang_EnumDecl_isScoped(cursor)) {
        auto spelling = clang_getCursorSpelling(cursor);
        auto kindSpelling = clang_getCursorKindSpelling(kind);

        if (WantedEnum(wanted, clang_getCString(spelling))) {
          entries.push_back(Entry{clang_getCString(spelling), {}});
        }

        clang_disposeString(spelling);
        clang_disposeString(kindSpelling);
      }

    } break;
    case CXCursorKind::CXCursor_EnumConstantDecl: {
      auto parentSpelling = clang_getCursorSpelling(parent);

      auto i = FindEntry(entries, clang_getCString(parentSpelling));
      if (i != -1) {
        auto spelling = clang_getCursorSpelling(cursor);

        entries[i].literals.push_back(clang_getCString(spelling));

        clang_disposeString(spelling);
      }

      clang_disposeString(parentSpelling);
    } break;
    default:
      break;
  }

  return CXChildVisit_Recurse;
}

struct Flag {
  const char* name{nullptr};
  bool active{false};
  char* value{nullptr};
};

static const char* fNamespace = "--namespace";
static const char* fIncludeGuard = "--include-guard";

static Flag gFlags[]{
    Flag{fNamespace},
    Flag{fIncludeGuard},
};
static const size_t gFlagsLen = sizeof(gFlags) / sizeof(Flag);

static Flag* FindFlag(const char* name, int n) {
  if (n == -1) n = strlen(name);
  for (size_t i = 0; i < gFlagsLen; ++i) {
    if (strncmp(name, gFlags[i].name, n) == 0) return &gFlags[i];
  }
  return nullptr;
}

static bool AllEnumsFound() {
  for (auto e : wanted) {
    if (FindEntry(entries, e) == -1) {
      std::fprintf(stderr, "enum '%s' not found\n", e);
      return false;
    }
  }
  return true;
}

static std::pair<int, char**> parseFlags(int argc, char** argv) {
  int n = 0;
  for (int i = 1; i < argc; ++i) {
    if (strncmp(argv[i], "--", 2) != 0) {
      // not a flag
      break;
    }
    auto sep = strchr(argv[i], '=');
    if (sep == nullptr) {
      std::fprintf(stderr, "flag '%s' has wrong format, must be --name=value\n",
                   argv[i]);
      exit(1);
    }
    const auto nameLen = sep - argv[i];
    auto f = FindFlag(argv[i], nameLen);
    if (f == nullptr) {
      argv[i][nameLen] = 0;
      std::fprintf(stderr, "unknown flag %s\n", argv[i]);
      exit(1);
    }
    f->active = true;
    f->value = sep + 1;
    ++n;
  }
  return {argc - n, argv + n};
}

static bool HasCorrectExt(const char* filename) {
  const auto dot = strchr(filename, '.');
  if (dot == nullptr) return false;
  const auto ext = dot + 1;
  if (strcmp(ext, "hpp") != 0 && strcmp(ext, "cpp") != 0 &&
      strcmp(ext, "cc") != 0)
    return false;
  return true;
}

std::vector<std::string> SplitNamespaces(std::string_view value) {
  if (value.empty()) return {};
  std::vector<std::string> r;
  auto v = value;
  for (size_t pos = 0, len = 0; pos < value.size(); pos += len + 2) {
    len = v.find("::");
    if (len == std::string_view::npos) len = v.size();
    r.push_back(std::string(value.data() + pos, len));
    v.remove_prefix(len + 2);
  }
  return r;
}

static const char* kVersion = "v0.1";

static const char* kUsage =
    R""""(Usage: enums [FLAGS] inputfile.[ch]pp enum_name1...enum_nameN

Flags:
    -h, --help             print this message
    --version              print version
    --namespace=value      add given namespace to the generated file
    --include-guard=value  add given include guard to the generated file)"""";

int main(int argc, char** argv) {
  if (argc < 2) {
    std::fprintf(stderr, "%s\n", kUsage);
    return 1;
  }

  if (argc > 1) {
    if (strcmp(argv[1], "--version") == 0) {
      std::printf("%s\n", kVersion);
      return 0;
    } else if (strcmp(argv[1], "--help") || strcmp(argv[1], "-h") == 0) {
      std::printf("%s\n", kUsage);
      return 0;
    }
  }

  std::tie(argc, argv) = parseFlags(argc, argv);

  if (argc < 2) {
    std::fprintf(stderr, "missing input file\n");
    return 1;
  }

  if (argc < 3) {
    std::fprintf(stderr, "missing enum name(s)\n");
    return 1;
  }

  auto filename = argv[1];

  if (!HasCorrectExt(filename)) {
    std::fprintf(stderr,
                 "incorrect file extension; must be one of .hpp, .cpp, .cc\n");
    return 1;
  }

  for (auto i = 2; i < argc; ++i) {
    wanted.push_back(argv[i]);
  }

  auto index = clang_createIndex(0, 0);

  CXTranslationUnit tu;
  auto err = clang_parseTranslationUnit2(index, filename, nullptr, 0, nullptr,
                                         0, CXTranslationUnit_None, &tu);
  if (err != CXError_Success) {
    std::fprintf(stderr, "error while parsing file: %d\n", err);
    return 1;
  }

  auto cursor = clang_getTranslationUnitCursor(tu);
  clang_visitChildren(cursor, visitor, nullptr);

  if (entries.empty()) {
    std::fprintf(stderr, "no enums found with the given names\n");
    return 1;
  }

  if (!AllEnumsFound()) return 1;

  const auto namespaceFlag = FindFlag(fNamespace, -1);
  const auto inGuardFlag = FindFlag(fIncludeGuard, -1);

  std::vector<std::string> namespaces;
  if (namespaceFlag->active) namespaces = SplitNamespaces(namespaceFlag->value);

  printf("// GENERATED FILE, DO NOT EDIT!\n\n");

  if (inGuardFlag->active) {
    printf("#ifndef %s\n#define %s\n\n", inGuardFlag->value,
           inGuardFlag->value);
  }
  if (namespaceFlag->active) {
    for (const auto& n : namespaces) printf("namespace %s {\n", n.c_str());
  }

  for (const auto& entry : entries) {
    printf("\nstatic const char* EnumNames_%s[] = {\n", entry.name.c_str());
    for (const auto& literal : entry.literals)
      printf("    \"%s::%s\",\n", entry.name.c_str(), literal.c_str());
    printf("};\n\n");

    printf(
        "inline const char* EnumName_%s(%s v)\n"
        "{\n"
        "    if (v < %s::%s || v > %s::%s)\n"
        "        return \"\";\n"
        "    const auto index = static_cast<int>(v) - "
        "static_cast<int>(%s::%s);\n"
        "    return EnumNames_%s[index];\n"
        "}\n",
        entry.name.c_str(), entry.name.c_str(), entry.name.c_str(),
        entry.literals.front().c_str(), entry.name.c_str(),
        entry.literals.back().c_str(), entry.name.c_str(),
        entry.literals.front().c_str(), entry.name.c_str());
  }

  if (namespaceFlag->active) {
    printf("\n");
    for (const auto& n : namespaces) printf("} // %s\n", n.c_str());
  }
  if (inGuardFlag->active) {
    printf("\n#endif\n");
  }

  clang_disposeTranslationUnit(tu);
  clang_disposeIndex(index);
}
