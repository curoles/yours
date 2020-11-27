/**@file
 * @brief     Term.
 * @author    Igor Lesik 2020
 * @copyright Igor Lesik 2020
 */
#pragma once

#include <string>

#include "lib/json.hpp"

namespace yours {

class Term
{
public:
    using Json = nlohmann::json;
    using VecStr = std::vector<std::string>;

private:
    Json json_;
    std::string name_;
    VecStr definitions_;

public:
    bool open(const std::string& path);

private:
    bool parse();
};

} // end namespace yours
