/**@file
 * @brief     SQLite to Prolog compiler.
 * @author    Igor Lesik 2020
 * @copyright Igor Lesik 2020
 */
#include "prolog.h"

//#include <iostream>

#include "sqlite.h"

yours::prolog::Compiler::~Compiler()
{
    f_.close();
}

bool
yours::prolog::Compiler::
compile(const std::string& sqlite_path)
{
    f_ << "/* GNU Prolog: gplc -o yours-prolog yours.prolog */\n";

    yours::sqlite::KB kb(sqlite_path);

    //FIXME TODO set SQLite flags for fast reading

    yours::sqlite::Term t;
    yours::sqlite::Domain d;
    std::string dterm_name, fact_val;

    for (const auto& fact : kb.db_.iterate<yours::sqlite::Fact>())
    {
        if (!kb.get_fact_term(fact, t, d)) continue;
        dterm_name = d.name + "__" + t.name;
        fact_val = fact.val;
        //std::cout << kb.db_.dump(fact) << std::endl;
        f_ << fact.name << "("
            << safe_var_name(dterm_name) << "," << safe_var_name(fact_val)
            << ")." << std::endl;
    }

    return true;
}

int
yours::prolog::
run_gplc(const std::string& prg_path, const std::string& exe_path)
{
    std::stringstream cmd;
    cmd << "gplc -o " << exe_path << " " << prg_path;

    return ::system(cmd.str().c_str());
}

bool
yours::prolog::
is_bad_var_name(const std::string& name)
{
    static const char VAR_CHARS[] =
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "01234567890_";

    std::size_t found = name.find_first_not_of(VAR_CHARS);

    return found != std::string::npos;
}

std::string&
yours::prolog::
safe_var_name(std::string& name)
{
    static const std::string q("'");

    if (is_bad_var_name(name)) {
        name = q + name + q;
    }

    return name;
}
