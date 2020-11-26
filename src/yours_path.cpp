/**@file
 * @brief     YOURS "path" entry.
 * @authors   Igor Lesik 2020
 * @copyright Igor Lesik 2020
 */
#include <cstdlib>

#include "yours/options.h"
#include "yours/trie_path.h"


int yours_path(yours::Options& options)
{
    std::string path;

    bool ok = yours::trie_path(options.name, path);

    if (ok) {
        printf("%s\n", path.c_str());
    }
    else {
        fprintf(stderr, "Error: malformed name, cant make path.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
