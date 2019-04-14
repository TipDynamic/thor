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

    if (thor::os::isdir("../"))
    {
        cout << colors::green << "and this is a " << colors::bold << colors::yellow << "dir.\n";
        vector<string> allFiles;
        allFiles = thor::os::list_files("../", true);
        cout << "list all files under it:\n";
        for (auto f : allFiles)
        {
            cout << f << endl;
        }
    }
    cout << colors::reset;

    string p = "/media/netac/a.mp4";
    string suffix = thor::os::suffix(p);
    cout << "suffix: " << suffix << endl;

    thor::Log(kInfo, "this a log test.");

    vector<float> a = {4.5, 6.5, 6, 7, 9};
    vector<float> b = {4.1, 3.5, 4, 7, 9};

    float res = thor::math::euclidean(a, b);
    cout << "euclidean res: " << to_string(res) << endl;

    return 0;
}
