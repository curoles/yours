/**@file
 * @brief     YOURS "compile" entry.
 * @authors   Igor Lesik 2020
 * @copyright Igor Lesik 2020
 */
#include <cstdlib>
#include <filesystem>
#include <fstream>

#include "yours/options.h"
#include "yours/trie_path.h"
#include "yours/term.h"

namespace fs = std::filesystem;

class TermCompiler
{

public:
    bool operator()(const std::string& path) {
        if (!fs::exists(path)) return false;
        return compile(path);
    }

    bool compile(const std::string& path);
};

bool TermCompiler::compile(const std::string& path)
{
    yours::Term term;
    if (!term.open(path)) return false;
    return true;
}

int compileProlog(const std::vector<std::string>& terms)
{
    std::ofstream prologFile;
    prologFile.open("yours.prolog");

    prologFile << "/* GNU Prolog: gplc -o yours-prolog yours.prolog*/\n";
    prologFile << "instance(theuniverse,iniverse).\n";

    printf("Compiling Prolog...\n");
    for (const auto& term : terms) {
        printf("%s\n", term.c_str());
    }

    prologFile.close();

    return 0;
}

int yours_compile(yours::Options& options)
{
    fs::directory_entry dir(options.dbPath);

    if (!dir.exists()) {
        fprintf(stderr, "Error: directory '%s' does not exist.\n", dir.path().c_str());
        return EXIT_FAILURE;
    }

    if (!dir.is_directory()) {
        fprintf(stderr, "Error: '%s' is not a directory.\n", dir.path().c_str());
        return EXIT_FAILURE;
    }

    TermCompiler compiler;

    bool ok = yours::trie_iterate(options.dbPath, compiler);

    if (!ok) {
        fprintf(stderr, "Error: cant find term files.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
