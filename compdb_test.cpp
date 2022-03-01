#include <unistd.h>

#include <cassert>
#include <cstdio>
#include <cstring>

#include "clang-c/CXCompilationDatabase.h"
#include "clang-c/Index.h"

static CXChildVisitResult visitor(CXCursor cursor, CXCursor parent,
                                  CXClientData client_data) {
  (void)client_data;

  auto spelling = clang_getCursorSpelling(cursor);
  auto parentSpelling = clang_getCursorSpelling(parent);
  auto kind = clang_getCursorKind(cursor);
  auto kindSpelling = clang_getCursorKindSpelling(kind);
  auto typeSpelling = clang_getTypeSpelling(clang_getCursorType(cursor));

  std::fprintf(stderr, "| -%s(%d), %s, %s\n", clang_getCString(kindSpelling),
               kind, clang_getCString(spelling),
               clang_getCString(typeSpelling));

  clang_disposeString(typeSpelling);
  clang_disposeString(spelling);
  clang_disposeString(kindSpelling);
  clang_disposeString(parentSpelling);

  return CXChildVisit_Recurse;
}

int main(int argc, char **argv) {
  if (argc < 3) {
    fprintf(stderr, "need 2 args: compilation database dir and filepath\n");
    return 1;
  }
  auto dbdir = argv[1];
  auto fpath = argv[2];

  CXCompilationDatabase db;
  {
    CXCompilationDatabase_Error err = CXCompilationDatabase_NoError;
    db = clang_CompilationDatabase_fromDirectory(dbdir, &err);
    if (!db) {
      fprintf(stderr, "Failed to load compilation database: %d\n", err);
      return 1;
    }
  }

  CXCompileCommands commands =
      clang_CompilationDatabase_getAllCompileCommands(db);
  assert(commands);

  const unsigned count = clang_CompileCommands_getSize(commands);

  CXCompileCommand matched = nullptr;
  for (unsigned i = 0; i < count; ++i) {
    CXCompileCommand command = clang_CompileCommands_getCommand(commands, i);
    assert(command);

    CXString fn = clang_CompileCommand_getFilename(command);

    const char *cstr = clang_getCString(fn);
    if (strcmp(cstr, fpath) == 0) {
      matched = command;
      clang_disposeString(fn);
      break;
    }
    clang_disposeString(fn);
  }

  const char *const *args = nullptr;
  int argsCount = 0;
  char **allocated = nullptr;

  if (matched) {
    argsCount = clang_CompileCommand_getNumArgs(matched);
    allocated = new char *[argsCount + 1];
    allocated[argsCount] = nullptr;
    for (int i = 0; i < argsCount; ++i) {
      CXString arg = clang_CompileCommand_getArg(matched, i);
      const char *cstr = clang_getCString(arg);
      allocated[i] = strdup(cstr);
      clang_disposeString(arg);
    }
    args = const_cast<const char *const *>(allocated);
  }

  clang_CompileCommands_dispose(commands);
  clang_CompilationDatabase_dispose(db);

  if (!matched) {
    fprintf(stderr, "Couldn't find anything matching: %s in %s\n", fpath,
            dbdir);
    return 1;
  }

  std::printf("%s was found in %s\n", fpath, dbdir);

  if (args != nullptr) {
    int offset = 1;
    if (access(argv[1], X_OK)) {
      ++offset;
    }
    args = const_cast<const char *const *>(&argv[offset]);
    argsCount = argc - offset;
  }

  auto index = clang_createIndex(0, 1);

  CXTranslationUnit tu;
  auto err = clang_parseTranslationUnit2(
      index, nullptr, args, argsCount, nullptr, 0, CXTranslationUnit_None, &tu);
  if (err != CXError_Success) {
    std::fprintf(stderr, "error while parsing file: %d\n", err);
    return 1;
  }

  auto ndiags = clang_getNumDiagnostics(tu);
  for (decltype(ndiags) i = 0; i < ndiags; ++i) {
    auto d = clang_getDiagnostic(tu, i);
    auto s = clang_formatDiagnostic(d, clang_defaultDiagnosticDisplayOptions());
    std::fprintf(stderr, "%s\n", clang_getCString(s));
    clang_disposeString(s);
    clang_disposeDiagnostic(d);
  }
  if (ndiags > 0) return 1;

  clang_visitChildren(clang_getTranslationUnitCursor(tu), visitor, nullptr);

  clang_disposeTranslationUnit(tu);
  clang_disposeIndex(index);

  return 0;
}
