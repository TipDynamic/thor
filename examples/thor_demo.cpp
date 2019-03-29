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


int main(int argc, char** argv) {

    cout << "Welcome!\n";
    cout << colors::bold << colors::yellow << "thor library\n" << colors::reset;

    if (argc < 2) {
      cout << colors::red << "send a path or file to test os module functionality.\n" << colors::reset << endl;
      exit(0);
    }

    if (thor::os::exists(argv[1])) {
        cout << argv[1] << " exist.\n";
        if (thor::os::isdir(argv[1])) {
            cout << colors::green << "and this is a " << colors::bold << colors::yellow << "dir.\n";
            vector<string> allFiles;
            allFiles = thor::os::list_files(argv[1], true);
            cout << "list all files under it:\n";
            for(auto f: allFiles) {
                cout << f << endl;
            }
        
        } else {
            cout << colors::green << "this is a file, and file name is: \n";
            cout << colors::bold << colors::yellow << thor::os::filename(argv[1]) << endl;
        }
    } else {
        cout << "this file or dir not exist.\n";
    }
    cout << colors::reset;

    int c = thor::math::add(2, 4);
    cout << c << endl;

    string p = "/media/netac/a.mp4";
    string suffix = thor::os::suffix(p);
    cout << "suffix: " << suffix << endl;

    thor::Log(kInfo, "this a log test.");

    Dog dog("Miny");
    thor::Log(kInfo, "My dog is " + dog.getName());
    thor::Log(kWarning, "His abilities: ");
    for (auto ab: dog.getAbilities()) {
        cout << ab << endl;
    }

    thor::Log(kInfo, "======== start test license checker...");

    // test slam
<<<<<<< HEAD:examples/thor_test.cpp
    Mat img1 = imread("../current.png");
    Mat img2 = imread("../pre.png");
    vector<cv::KeyPoint> kp1;
    vector<cv::KeyPoint> kp2;
    vector<DMatch> good_matches;
    slam::getGoodMatchesColor(img1, img2, good_matches, kp1, kp2, true);
    cout << "\nkeypoint 1: " << kp1.size() << endl;
    cout << "keypoint 2: " << kp2.size() << endl;
    cout << "get all matches: " << good_matches.size() << endl;
=======
//    Mat img1 = imread("../current.png");
//    Mat img2 = imread("../pre.png");
//    vector<cv::KeyPoint> kp1;
//    vector<cv::KeyPoint> kp2;
//    vector<DMatch> good_matches;
//    slam::getGoodMatchesColor(img1, img2, good_matches, kp1, kp2, true);
//    cout << "\nkeypoint 1: " << kp1.size() << endl;
//    cout << "keypoint 2: " << kp2.size() << endl;
//    cout << "get all matches: " << good_matches.size() << endl;

    thor::security::LicenseChecker licenseChecker;
    thor::security::CheckResult res =
            licenseChecker.checkLicense("ad4ded4a0d73ca76f9e5c2241a4e8d7643ab5478a1b2aefa02d20ee00928e16b");
    LOG(INFO) << res.ok;
//    LOG(INFO) << res;
    LOG(INFO) << res.msg;
>>>>>>> 01f1be066e964875a43cb1b9cb38bbde3d10bc20:examples/thor_demo.cpp

    return 0;
}
