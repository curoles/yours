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

namespace fs = std::filesystem;

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

    std::vector<std::string> terms;

    bool ok = yours::trie_list(options.dbPath, terms);

    if (ok) {
        if (options.compile.prolog) {
            compileProlog(terms);
        }
    }
    else {
        fprintf(stderr, "Error: cant find term files.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
