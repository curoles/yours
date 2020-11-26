/**@file
 * @brief     Trie path to file.
 * @author    Igor Lesik 2020
 * @copyright Igor Lesik 2020
 */
#include "trie_path.h"

#include <filesystem>

/// Make FS trie path with given name.
///
/// @return true if `name` is well formed and FS path can be created.
///
bool yours::trie_path(const std::string& name, std::string& path)
{
    for (const auto& c : name) {
        path += c;
        path += std::filesystem::path::preferred_separator;
    }

    path += name;

    return true;
}
