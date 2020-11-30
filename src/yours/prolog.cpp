/**@file
 * @brief     SQLite to Prolog compiler.
 * @author    Igor Lesik 2020
 * @copyright Igor Lesik 2020
 */
#include "prolog.h"

#include <regex>
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
    std::string dterm_name, fact_name, fact_val;

    for (const auto& fact : kb.db_.iterate<yours::sqlite::Fact>())
    {
        if (!kb.get_fact_term(fact, t, d)) continue;
        dterm_name = d.name + "__" + t.name;
        to_var_name(dterm_name);
        fact_name = fact.name;
        to_var_name(fact_name);
        fact_val = fact.val;
        to_var_name(fact_val);
        //std::cout << kb.db_.dump(fact) << std::endl;
        f_ << fact_name << "("
            << dterm_name << "," << fact_val
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

    if (name.empty()) return true;

    if (::isupper(name[0])) return true;

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

std::string&
yours::prolog::
to_var_name(std::string& name)
{
    static const std::regex re("::");
    name = std::regex_replace(name, re, "__");

    safe_var_name(name);

    rename_builtin(name);

    return name;
}

std::string&
yours::prolog::
rename_builtin(std::string& name)
{
    static const std::string prefix{"kb_"};
    static const char* builtin[] = {"is"};

    for (unsigned int i = 0; i < sizeof(builtin)/sizeof(builtin[0]); ++i) {
        if (name.compare(builtin[i]) == 0) {
            name = prefix + name;
            break;
        }
    }

    return name;
}

