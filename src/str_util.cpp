//
// Created by jintian on 7/14/17.
//

// this file enables lots of string extend methods

#include "include/str_util.h"

using namespace std;


void thor::str_util::SplitString(const std::string &s, std::vector<std::string> &v, const std::string &c)
{
    std::string::size_type pos1, pos2;
    pos2 = s.find(c);

    if (pos2 > s.size()){
        // indicates delimiter not in this string
        // return this string as vector
        v.push_back(s);
    } else {
        pos1 = 0;
        while(std::string::npos != pos2)
        {
            v.push_back(s.substr(pos1, pos2-pos1));

            pos1 = pos2 + c.size();
            pos2 = s.find(c, pos1);
        }
        if(pos1 != s.length()) {
            v.push_back(s.substr(pos1));
        }
    }
}

string thor::str_util::join_str(const std::string &c, vector<string> s_v) {
    string result_s = "";
    for (auto it = s_v.begin(); it < s_v.end() - 1; ++it) {
        result_s += (*it + c);
    }
    result_s += s_v.back();
    return result_s;
}

/**
 * Strip C from string vector and return a new string vector
 * @param s_v
 * @param c
 * @return
 */
void thor::str_util::StripString(vector<string> s_v, const string &c) {
    for (auto it = s_v.begin(); it < s_v.end(); it++) {
        if (*it == c) {
            s_v.erase(it);
        }
    }
}

/***
 * Replace part of string from original string
 * @param str
 * @param from
 * @param to
 * @return
 */
bool thor::str_util::Replace(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

/**
 * Replace all part of string
 * @param str
 * @param from
 * @param to
 */
void thor::str_util::ReplaceAll(std::string& str, const std::string& from, const std::string& to) {
    if(from.empty())
        return;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}