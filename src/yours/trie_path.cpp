/**@file
 * @brief     Trie path to file.
 * @author    Igor Lesik 2020
 * @copyright Igor Lesik 2020
 */
#include "trie_path.h"

#include <filesystem>

namespace fs = std::filesystem;

/// Make FS trie path from given name.
///
/// @return true if `name` is well formed and FS path can be created.
///
bool yours::trie_path(
    const std::string& name,
    std::string& path
)
{
    for (const auto& c : name) {
        path += c;
        path += fs::path::preferred_separator;
    }

    path += name;

    return true;
}

bool yours::trie_list(
    const std::string& dbPath,
    std::vector<std::string>& terms
)
{
    fs::directory_entry dir(dbPath);

    if (!dir.exists() or !dir.is_directory()) return false;

    for (const auto& p : fs::recursive_directory_iterator(dir)) {
        if (p.is_regular_file()) {
            terms.push_back(p.path().string());
        }
    }

    return true;
}

bool yours::trie_iterate(
    const std::string& dbPath,
    std::function<bool(const std::string&)> callback
)
{
    fs::directory_entry dir(dbPath);

    if (!dir.exists() or !dir.is_directory()) return false;

    for (const auto& p : fs::recursive_directory_iterator(dir)) {
        if (p.is_regular_file()) {
            bool ok = callback(p.path().string());
            if (!ok) break;
        }
    }

    return true;
}

bool yours::trie_get_name_from_path(
    const std::string& path,
    std::string& name
)
{
    name = fs::path(path).filename();

    // remove trailing ".json"
    name.erase(name.end()-5, name.end());

    // FIXME TODO check that trie path corresponds the name

    return true;
}
