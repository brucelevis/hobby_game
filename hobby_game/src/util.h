#pragma once

#include <string>
#include <vector>

namespace hg
{
    /*
        Splits a string (str) into an array of smaller strings (out) delimited by (delim - which can be multiple delimiters).
    */
    void split_string(const std::string& str, const char* delim, int num_delim, std::vector<std::string>& out);
}