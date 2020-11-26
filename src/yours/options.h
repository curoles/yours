/**@file
 * @brief  YOURS command line arguments.
 * @author Igor Lesik 2020
 */
#pragma once

#include <string>
#include <cstdint>

namespace yours {

struct Options
{
    enum {
        CMD_UNKNOWN = 0,
        CMD_PATH,
        CMD_LIST,
        CMD_COMPILE
    } cmd{CMD_UNKNOWN};

    std::string name;
    std::string dbPath;

    struct Compile {
        bool prolog = false;
    } compile;



    bool parse(int argc, char** argv);
};

} // namespace yours
