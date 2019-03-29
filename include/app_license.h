// ************************************
// Copyrights by Jin Fagang
// 2/15/19-15-17
// app_license
// jinfagang19@gmail.com
// CTI Robotics
// ************************************

//
// Created by jintain on 2/15/19.
//

#ifndef THOR_APP_LICENSE_H
#define THOR_APP_LICENSE_H

/**
 * this is using for license check, we need to check license when
 * executing init() function in our applications
 */

#include <iostream>
#include "curl/curl.h"
#include "glog/logging.h"
#include "json.hpp"

using namespace google;
using namespace std;
using json = nlohmann::json;

namespace thor{
    namespace security{


        struct CheckResult{
            bool ok;
            string msg;
        };


        class LicenseChecker{
        public:
            LicenseChecker();
            CheckResult checkLicense(string license);
            static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);

        private:
            // add ?license=dferfgye5894569 do get request to get license result
            // if success
            string _url;

        };
    }
}

#endif //THOR_APP_LICENSE_H
