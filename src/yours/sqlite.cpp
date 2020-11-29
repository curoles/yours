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

bool KB::find_dterm(unsigned int term_id, unsigned int domain_id, unsigned int& id)
{
    using namespace sqlite_orm;
    auto terms = db_.get_all<DTerm>(
        where(c(&DTerm::term_id) == term_id and c(&DTerm::domain_id) == domain_id));

    if (terms.size() < 1) return false;

    id = terms[0].id;

    return true;
}

bool KB::find_fact(unsigned int term_id, const std::string& name, unsigned int& id)
{
    using namespace sqlite_orm;
    auto facts = db_.get_all<Fact>(
        where(c(&Fact::term_id) == term_id and c(&Fact::name) == name));

    if (facts.size() < 1) return false;

    id = facts[0].id;

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
            yours::sqlite::DTerm dt {id: 0, term_id: t.id, domain_id: d.id};
            if (!find_dterm(t.id, d.id, dt.id)) {dt.id = db_.insert(dt);}
            this->insert_term_definition(term, dt.id, domain_name);
        }

        return true;
    });

    return true;
}

bool KB::insert_term_definition(
    const yours::Term& term,
    unsigned int term_id,
    const std::string& domain_name
)
{
    auto definition = term.json_.at(domain_name);

    for (const auto& fact : definition.items()) {
        Fact f {id: 0, term_id: term_id, name: fact.key(), val: fact.value()};
        if (find_fact(term_id, f.name, f.id)) {
            db_.update(f);
        }
        else {
            f.id = db_.insert(f);
        }
    }

    return true;
}

bool KB::get_fact_term(const Fact& fact, Term& term, Domain& domain)
{
    if (auto dterm = db_.get_pointer<DTerm>(fact.term_id)) {
        if (auto domain_ptr = db_.get_pointer<Domain>(dterm->domain_id)) {
            if (auto term_ptr = db_.get_pointer<Term>(dterm->term_id)) {
                term = *term_ptr;
                domain = *domain_ptr;
                return true;
            }
        }
    }

    return false;
}
