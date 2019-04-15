//
// Created by JinTian on 02/01/2018.
//

#ifndef CAO_MATH_H
#define CAO_MATH_H


#include "vector"
#include "assert.h"
#include <cmath>
#include "glog/logging.h"

using namespace google;
using namespace std;
/**
 *  A math module do higher calculate
 */

namespace thor{
    namespace math{
        // need a template method calculate
        // 
        template<typename T>
        inline T euclidean(vector<T> const& v_a, 
        vector<T> const& v_b) {
            assert(v_a.size() == v_b.size());
            T sum = 0.;
            for(size_t i = 0; i < v_a.size(); i++)
            {
                sum += pow(v_a[i] - v_b[i], 2);
            }
            sum = sqrt(sum);
            return sum;
        }
    }
}




#endif //CAO_MATH_H
