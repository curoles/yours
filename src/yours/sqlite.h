/**@file
 * @brief     Compile JSON representation to SQLite representation.
 * @author    Igor Lesik 2020
 * @copyright Igor Lesik 2020
 */
#pragma once

#include <string>
//#include <any> //<variant>

#include "lib/sqlite_orm.h"
#include "term.h"


namespace yours::sqlite {

using Variant = std::string;//std::any;//variant<int, std::string>;

struct Term {
    unsigned int id;
    std::string name;
};

// Term may have several definitions from different K-domains.
struct Domain {
    unsigned int id;
    std::string name;
};

struct DTerm {
    unsigned int id;
    unsigned int term_id;
    unsigned int domain_id;
};

struct Fact {
    unsigned int id;
    unsigned int term_id;
    std::string name;
    Variant val;
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
            make_column("Name", &Domain::name, unique())),
        make_table("DTerm",
            make_column("Id", &DTerm::id, primary_key()),
            make_column("TermId", &DTerm::term_id),
            make_column("DomainId", &DTerm::domain_id),
            unique(&DTerm::term_id, &DTerm::domain_id)),
        make_table("Fact",
            make_column("Id", &Fact::id, primary_key()),
            make_column("TermId", &Fact::term_id),
            make_column("Name", &Fact::name),
            make_column("Value", &Fact::val),
            unique(&Fact::term_id, &Fact::name))
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

    bool find_dterm(unsigned int term_id, unsigned int domain_id, unsigned int& id);

    bool find_fact(unsigned int term_id, const std::string& name, unsigned int& id);

    bool get_fact_term(const Fact& fact, Term& term, Domain& domain);

private:
    bool insert_term_definition(
        const yours::Term& term,
        unsigned int term_id,
        const std::string& domain_name
    );
};

} // end namespace yours::sqlite
