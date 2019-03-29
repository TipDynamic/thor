//
// Created by jintian on 7/14/17.
//

#ifndef _T_STRING_H
#define _T_STRING_H

#include <string>
#include <iostream>
#include <vector>

using namespace std;

namespace thor{
    namespace str_util{

        void SplitString(const std::string &s, std::vector<std::string> &v, const std::string &c);
        string join_str(const std::string &c, vector<string> s_v);

        void StripString(vector<string> s_v, const string &c);

        bool Replace(std::string& str, const std::string& from, const std::string& to);
        void ReplaceAll(std::string& str, const std::string& from, const std::string& to);
    }
}

#endif //_T_STRING_H
