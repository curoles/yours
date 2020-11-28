/**@file
 * @brief     YOURS "sqlite-show" entry.
 * @authors   Igor Lesik 2020
 * @copyright Igor Lesik 2020
 */
#include <cstdlib>
#include <algorithm>
#include <iostream>

#include "yours/options.h"
#include "yours/sqlite.h"


int yours_sqlite_show(yours::Options& options)
{
    yours::sqlite::KB kb(options.db_path);

    std::string name = options.name;

    std::transform(name.begin(), name.end(), name.begin(), ::tolower);

    if (name == "term") {
        for (const auto& term : kb.db_.iterate<yours::sqlite::Term>()) {
            std::cout << kb.db_.dump(term) << std::endl;
        }
    }
    else if (name == "domain") {
        for (const auto& domain : kb.db_.iterate<yours::sqlite::Domain>()) {
            std::cout << kb.db_.dump(domain) << std::endl;
        }
    }
    else if (name == "dterm") {
        for (const auto& term : kb.db_.iterate<yours::sqlite::DTerm>()) {
            std::cout << kb.db_.dump(term) << std::endl;
        }
    }
    else if (name == "fact") {
        for (const auto& fact : kb.db_.iterate<yours::sqlite::Fact>()) {
            std::cout << kb.db_.dump(fact) << std::endl;
        }
    }

    return EXIT_SUCCESS;
}
