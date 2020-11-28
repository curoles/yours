/**@file
 * @brief     Convert JSON representation to SQLite representation.
 * @author    Igor Lesik 2020
 * @copyright Igor Lesik 2020
 */
#include "sqlite.h"


using namespace yours::sqlite;


bool KB::find_term(const std::string& name, unsigned int& id)
{
    using namespace sqlite_orm;
#if 0 //FIXME TODO compile error from table name collector
    static auto statement =
        db_.prepare(select(&Term::id, where(c(&Term::name) == std::string("name"))));
        //db_.prepare(select(&Term::id, where(is_equal(&Term::name, std::string()))));*/

    get<0>(statement) = name;
    auto ids = db_.execute(statement);

    if (ids.size() < 1) return false;

    id = ids[0];
#else
    auto terms = db_.get_all<Term>(where(c(&Term::name) == name));

    if (terms.size() < 1) return false;

    id = terms[0].id;
#endif

    return true;
}

bool KB::find_domain(const std::string& name, unsigned int& id)
{
    using namespace sqlite_orm;
    auto domains = db_.get_all<Domain>(where(c(&Domain::name) == name));

    if (domains.size() < 1) return false;

    id = domains[0].id;

    return true;
}

bool KB::compile(const yours::Term& term)
{
    yours::sqlite::Term t {id: 0, name: term.name_};

    db_.transaction([&]{
        if (!find_term(t.name, t.id)) {t.id = db_.insert(t);}
        for (const std::string& domain_name : term.definitions_) {
            yours::sqlite::Domain d {id: 0, name: domain_name};
            if (!find_domain(d.name, d.id)) {d.id = db_.insert(d);}
            this->insert_term_definition(term, t.id, domain_name, d.id);
        }

        return true;
    });

    return true;
}

bool KB::insert_term_definition(
    const yours::Term& term,
    unsigned int term_id,
    const std::string& domain_name,
    unsigned int domain_id
)
{
(void)term;(void)term_id;(void)domain_id;(void)domain_name;

    return true;
}
