/**@file
 * @brief     YOURS entry.
 * @authors   Igor Lesik 2020
 * @copyright Igor Lesik 2020
 */
#include <cstdlib>

#include "yours/options.h"


int yours_path(yours::Options& options);
int yours_list(yours::Options& options);
int yours_compile(yours::Options& options);
int yours_sqlite_show(yours::Options& options);

int main(int argc, char** argv)
{
    yours::Options options;

    options.parse(argc, argv);

    switch (options.cmd)
    {
        case yours::Options::CMD_PATH:
            return yours_path(options);
        case yours::Options::CMD_LIST:
            return yours_list(options);
        case yours::Options::CMD_COMPILE:
            return yours_compile(options);
        case yours::Options::CMD_SQLITE_SHOW:
            return yours_sqlite_show(options);
        case yours::Options::CMD_UNKNOWN:
        default:
            fprintf(stderr, "Error: Unknown command\n");
            return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
