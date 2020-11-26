/**@file
 * @brief     Trie path to file.
 * @author    Igor Lesik 2020
 * @copyright Igor Lesik 2020
 */
#pragma once

#include <string>
#include <vector>

namespace yours {

bool trie_path(const std::string& name, std::string& path);

bool trie_list(const std::string& dbPath, std::vector<std::string>& terms);

} // end namespace yours
