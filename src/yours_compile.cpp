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
#include "yours/sqlite.h"
#include "yours/prolog.h"

namespace fs = std::filesystem;

class TermCompiler
{
    yours::sqlite::KB sqlite_kb_;
public:
    TermCompiler(const std::string& path):
        sqlite_kb_(path)
    {
        sqlite_kb_.sync_schema();
    }

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

    return sqlite_kb_.compile(term);
}

int yours_compile(yours::Options& options)
{
    fs::directory_entry dir(options.db_path);

    if (!dir.exists()) {
        fprintf(stderr, "Error: directory '%s' does not exist.\n", dir.path().c_str());
        return EXIT_FAILURE;
    }

    if (!dir.is_directory()) {
        fprintf(stderr, "Error: '%s' is not a directory.\n", dir.path().c_str());
        return EXIT_FAILURE;
    }

    std::string sqlite_path = "yours.sqlite";

    if (options.compile.sqlite) {
        TermCompiler compiler(sqlite_path);

        printf("Creating SQLite %s...\n", sqlite_path.c_str());

        bool ok = yours::trie_iterate(options.db_path, compiler);

        if (!ok) {
            fprintf(stderr, "Error: cant find term files.\n");
            return EXIT_FAILURE;
        }
    }

    if (options.compile.prolog) {
        if (!fs::exists(sqlite_path)) {
            fprintf(stderr, "Error: file %s does not exist.\n", sqlite_path.c_str());
            return EXIT_FAILURE;
        }
        std::string prolog_path = "yours.prolog";
        printf("Creating Prolog %s...\n", prolog_path.c_str());
        yours::prolog::Compiler prolog(prolog_path);
        bool ok = prolog.compile(sqlite_path);
        if (!ok) {
            fprintf(stderr, "Error: failed to generate Prolog.\n");
            return EXIT_FAILURE;
        }
        //TODO if (options.compile.gplc)
        std::string gprolog_exe{"yours-prolog"};
        printf("Creating GNU Prolog executable %s...\n", gprolog_exe.c_str());
        int gplc_res = yours::prolog::run_gplc(prolog_path, gprolog_exe);
        if (gplc_res != EXIT_SUCCESS) {
            fprintf(stderr, "Error: failed to generate GNU Prolog executable.\n");
        }
    }

    return EXIT_SUCCESS;
}
