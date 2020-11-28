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
    std::string name;
};

// Term may have several definitions from different K-domains.
struct Domain {
    unsigned int id;
    std::string name;
};

static inline
auto create(const std::string& path) {
    using namespace sqlite_orm;
    return make_storage(path,
        make_table("Term",
            make_column("Id", &Term::id, primary_key()),
            make_column("Name", &Term::name, unique())),
        make_table("Domain",
            make_column("Id", &Domain::id, primary_key()),
            make_column("Name", &Domain::name, unique()))

    );
}


/// Knowledge Base in SQLite format.
///
class KB
{
public:
    using DB = decltype(yours::sqlite::create(""));

    DB db_;

public:
    KB(const std::string& path):
        db_(yours::sqlite::create(path)) {
    }

    void sync_schema() {db_.sync_schema();}

    bool compile(const yours::Term& term);

    bool find_term(const std::string& name, unsigned int& id);

    bool find_domain(const std::string& name, unsigned int& id);

private:
    bool insert_term_definition(
        const yours::Term& term,
        unsigned int term_id,
        const std::string& domain_name,
        unsigned int domain_id
    );
};

} // end namespace yours::sqlite
