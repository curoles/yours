/**@file
 * @brief  YOURS command line arguments parser.
 * @author Igor Lesik 2020
 */
#include "options.h"

// https://github.com/CLIUtils/CLI11
#include "lib/CLI11.hpp"

bool yours::Options::parse(int argc, char** argv)
{
    CLI::App app{"YOURS"};

    // See https://cliutils.gitlab.io/CLI11Tutorial/chapters/subcommands.html
    app.require_subcommand(/*min*/ 0, /*max*/ 1);

    CLI::App* subcmdPath = app.add_subcommand("path", "Get trie-path by name");

    subcmdPath->add_option("name", this->name, "name")
        ->required();

#if 0
    this->testCfgFileName = "test.json";
    app.add_option("-f,--file", this->testCfgFileName, "path to a test file")->
        check(CLI::ExistingFile);

    this->isSeedGiven = 0;
    this->randSeed = 420;
    app.add_option("-s,--seed", this->randSeed, "seed for Random Number Generator")->
        each([this](const std::string &){++this->isSeedGiven;});
#endif

    try {
        app.parse(argc, argv);
    } catch (const CLI::ParseError& e) {
        return app.exit(e);
    }

    if (app.got_subcommand("path")) this->cmd = CMD_PATH;

    return true;
}
