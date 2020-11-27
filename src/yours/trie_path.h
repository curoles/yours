/**@file
 * @brief     Trie path to file.
 * @author    Igor Lesik 2020
 * @copyright Igor Lesik 2020
 */
#pragma once

#include <string>
#include <vector>
#include <functional>

namespace yours {

bool trie_path(
    const std::string& name,
    std::string& path
);

bool trie_list(
    const std::string& dbPath,
    std::vector<std::string>& terms
);

bool trie_iterate(
    const std::string& dbPath,
    std::function<bool(const std::string&)> callback
);

bool trie_get_name_from_path(
    const std::string& path,
    std::string& name
);

} // end namespace yours
