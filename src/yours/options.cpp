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

    CLI::App* cmdPath = app.add_subcommand("path", "Get trie-path by name of term");

    cmdPath->add_option("name", this->name, "name of term")
        ->required();

    CLI::App* cmdList = app.add_subcommand("list", "List all terms in DB");

    cmdList->add_option("db", this->db_path, "path to DB")
        ->required()
        ->check(CLI::ExistingDirectory);

    CLI::App* cmdCompile = app.add_subcommand("compile", "Transform terms into some representation");

    cmdCompile->add_option("db", this->db_path, "path to DB")
        ->required()
        ->check(CLI::ExistingDirectory);

    cmdCompile->add_flag("--prolog", this->compile.prolog, "Create Prolog file");

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
    else if (app.got_subcommand("list")) this->cmd = CMD_LIST;
    else if (app.got_subcommand("compile")) this->cmd = CMD_COMPILE;

    return true;
}
