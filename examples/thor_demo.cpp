//
// Created by JinTian on 02/01/2018.
//

/**
 * A simple example of using Thor library
 */

#include <iostream>
#include "thor/colors.h"
#include "thor/os.h"
#include "thor/math.h"
#include "thor/logging.h"
#include "thor/slam.h"
#include "opencv2/core.hpp"
#include "opencv2/opencv.hpp"
#include "./include/dog.h"
#include "thor/app_license.h"

using namespace std;
using namespace thor;
using namespace cv;

int main(int argc, char **argv)
{

    cout << "Welcome!\n";
    cout << colors::bold << colors::yellow << "thor library\n"
         << colors::reset;

    if (argc < 2)
    {
        cout << colors::red << "send a path or file to test os module functionality.\n"
             << colors::reset << endl;
        exit(0);
    }

    if (thor::os::exists(argv[1]))
    {
        cout << argv[1] << " exist.\n";
        if (thor::os::isdir(argv[1]))
        {
            cout << colors::green << "and this is a " << colors::bold << colors::yellow << "dir.\n";
            vector<string> allFiles;
            allFiles = thor::os::list_files(argv[1], true);
            cout << "list all files under it:\n";
            for (auto f : allFiles)
            {
                cout << f << endl;
            }
        }
        else
        {
            cout << colors::green << "this is a file, and file name is: \n";
            cout << colors::bold << colors::yellow << thor::os::filename(argv[1]) << endl;
        }
    }
    else
    {
        cout << "this file or dir not exist.\n";
    }
    cout << colors::reset;

    thor::Log(kInfo, "start test thor list recurse files...");
    vector<string> all_files = thor::os::list_files_recurse(argv[1], false);
    for (auto p : all_files)
    {
        cout << p << endl;
    }

    int c = thor::math::add(2, 4);
    cout << c << endl;

    string p = "/media/netac/a.mp4";
    string suffix = thor::os::suffix(p);
    cout << "suffix: " << suffix << endl;

    thor::Log(kInfo, "this a log test.");

    Dog dog("Miny");
    thor::Log(kInfo, "My dog is " + dog.getName());
    thor::Log(kWarning, "His abilities: ");
    for (auto ab : dog.getAbilities())
    {
        cout << ab << endl;
    }

    thor::Log(kInfo, "======== start test license checker...");

    return 0;
}
