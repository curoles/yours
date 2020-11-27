/**@file
 * @brief     YOURS "list" entry.
 * @authors   Igor Lesik 2020
 * @copyright Igor Lesik 2020
 */
#include <cstdlib>
#include <filesystem>

#include "yours/options.h"
#include "yours/trie_path.h"

namespace fs = std::filesystem;


int yours_list(yours::Options& options)
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

    bool ok = yours::trie_iterate(
        options.dbPath,
        [](const std::string& term_path) {
            printf("%s\n", term_path.c_str());
            return true;
        }
    );

    if (!ok) {
        fprintf(stderr, "Error: cant find term files.\n");
        return EXIT_FAILURE;
    }

#if 0
    std::vector<std::string> terms;

    bool ok = yours::trie_list(options.dbPath, terms);

    if (ok) {
        for (const auto& term : terms) {
            printf("%s\n", term.c_str());
        }
    }
    else {
        fprintf(stderr, "Error: cant find term files.\n");
        return EXIT_FAILURE;
    }
#endif

    return EXIT_SUCCESS;
}
