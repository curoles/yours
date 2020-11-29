/**@file
 * @brief     SQLite to Prolog compiler.
 * @author    Igor Lesik 2020
 * @copyright Igor Lesik 2020
 */
#pragma once

#include <string>
#include <fstream>

namespace yours::prolog {

class Compiler
{
    std::string path_;
    std::ofstream f_;

public:
    Compiler(const std::string prolog_path):
        path_(prolog_path)
    {
        f_.open(path_);
    }

   ~Compiler();

    bool compile(const std::string& sqlite_path);
};

int run_gplc(const std::string& prg_path, const std::string& exe_path);

bool is_bad_var_name(const std::string& name);

std::string& safe_var_name(std::string& name);

} // namespace yours::prolog
