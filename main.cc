#include <clang-c/Index.h>

#include <cstring>
#include <functional>
#include <iostream>
#include <vector>

struct Entry {
  std::string name;
  std::vector<std::string> literals;
};

int FindEntry(const std::vector<Entry>& entries, const char* name) {
  for (size_t i = 0; i < entries.size(); ++i)
    if (std::strcmp(entries[i].name.c_str(), name) == 0) return i;
  return -1;
}

char* needle{nullptr};

std::vector<Entry> entries;

std::vector<const char*> wanted;

bool WantedEnum(std::vector<const char*> wanted, const char* name) {
  for (auto e : wanted)
    if (std::strcmp(e, name) == 0) return true;
  return false;
}

CXChildVisitResult visitor(CXCursor cursor, CXCursor parent,
                           CXClientData client_data) {
  auto kind = clang_getCursorKind(cursor);

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

int main(int argc, char** argv) {
  if (argc < 2) {
    std::fprintf(stderr, "missing input file\n");
    return 1;
  }

  if (argc < 3) {
    std::fprintf(stderr, "missing enum name(s)\n");
    return 1;
  }

  for (auto i = 2; i < argc; ++i) {
    wanted.push_back(argv[i]);
  }

  auto index = clang_createIndex(0, 0);

  auto translationUnit = clang_parseTranslationUnit(
      index, argv[1], nullptr, 0, nullptr, 0, CXTranslationUnit_None);
  if (translationUnit == nullptr) {
    std::cerr << "Unable to parse translation unit. Quitting.\n";
    return 1;
  }

  auto cursor = clang_getTranslationUnitCursor(translationUnit);
  clang_visitChildren(cursor, visitor, nullptr);

  for (const auto& entry : entries) {
    std::printf("%s: {", entry.name.c_str());
    for (const auto& literal : entry.literals) {
      std::printf("%s,", literal.c_str());
    }
    std::printf("}\n");
  }

  clang_disposeTranslationUnit(translationUnit);
  clang_disposeIndex(index);
}
