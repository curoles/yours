/**@file
 * @brief     Compile JSON representation to SQLite representation.
 * @author    Igor Lesik 2020
 * @copyright Igor Lesik 2020
 */
#pragma once

#include <string>

#include "lib/sqlite_orm.h"
#include "term.h"


namespace yours::sqlite {

struct Term {
    unsigned int id;
};

static inline
auto create(const std::string& path) {
    using namespace sqlite_orm;
    return make_storage(path,
        make_table("Term",
            make_column("Id", &Term::id, primary_key()))
    );
}


/// Knowledge Base in SQLite format.
///
class KB
{
    using DB = decltype(yours::sqlite::create(""));

    DB db_;

public:
    KB(const std::string& path):
        db_(yours::sqlite::create(path)) {
    }

    bool compile(const yours::Term& term);
};

} // end namespace yours::sqlite
