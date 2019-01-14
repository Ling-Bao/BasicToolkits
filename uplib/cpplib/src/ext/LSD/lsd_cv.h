/************************************************************
	> Author: ling
	> Mail: @mango.com
	> Created Time: 09/14/2018
************************************************************/

#ifndef CPPLIB_LSD_CV_H
#define CPPLIB_LSD_CV_H

extern "C"
{
#include "ext/LSD/lsd.h"
}

#include <opencv2/imgproc.hpp>

namespace cpplib {
    class LSD {
    public:
        LSD();

        ~LSD();

        void LineDetectByC(cv::Mat &image, std::vector<std::vector<double> > &lines, double length);

        void LineDetectByCv(cv::Mat &image, std::vector<std::vector<double> > &lines, double length);

    };
}

#endif //CPPLIB_LSD_CV_H
