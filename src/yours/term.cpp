/**@file
 * @brief     Term.
 * @author    Igor Lesik 2020
 * @copyright Igor Lesik 2020
 */
#include "term.h"

#include <fstream>
#include <iostream>

#include "trie_path.h"


bool yours::Term::open(const std::string& path)
{
    std::ifstream jsonFile(path); // open file

    if (!jsonFile.is_open()) return false;

    jsonFile >> json_; // read JSON file
    jsonFile.close();

    if (!yours::trie_get_name_from_path(path, name_)) return false;

    //printf("%s, %s\n", name_.c_str(), path.c_str());

    return parse();
}

bool yours::Term::parse()
{
    // Term is a list of definitions, each definition has form
    // domain:definition, where domain type is string.
#if 0
    for (const auto& [domain, definition] : json_.items()) {
        std::cout << domain << " : " << definition << "\n";
    }
#endif

    for (const auto& el : json_.items()) {
        //std::cout << el.key() << " : " << el.value() << "\n";
        definitions_.emplace_back(el.key());
    }

    return true;
}

