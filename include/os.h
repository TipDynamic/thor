//
// Created by jintian on 7/14/17.
//

#ifndef _T_OS_H
#define _T_OS_H

#include <iostream>
#include <string>
#include <vector>

#include <sys/types.h>
#include <sys/stat.h>
#include <cassert>
#include "logging.h"

using namespace std;

namespace thor{

    namespace os{
        bool exists(string path);
        bool isdir(string path);
        bool isfile(string path);

        vector<string> list_files(string path, bool full_path);
        vector<string> list_files_recurse(string path, bool full_path);
        vector<string> list_dirs(string path, bool full_path);
        vector<string> list_all(string path, bool full_path);

        string join(string path, string filename);

        string parent_path(string path);
        string filename(string path);

        int do_mkdir(string path, mode_t mode);
        int makedirs(string path, mode_t mode);

        string abs_path(string path);

        string suffix(string path);
    }
}

// Define some micros to check the method params is null or not.
#define CHECK_NULL(param) (if (param == NULL) cout << "got null.\n";)

#endif //_OS_H
