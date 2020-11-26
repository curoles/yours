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
    //or !dir.is_directory()) return false;

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

    return EXIT_SUCCESS;
}
