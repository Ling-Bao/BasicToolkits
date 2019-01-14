/************************************************************
	> Author: ling
	> Mail: @mango.com
	> Created Time: 09/14/2018
************************************************************/

#include "lsd_cv.h"

using namespace cpplib;

LSD::LSD() {}

LSD::~LSD() {}

void LSD::LineDetectByC(cv::Mat &image, std::vector<std::vector<double> > &lines, double length) {
    // implement by c
    cv::Mat gray_image;
    if (image.channels() == 1)
        gray_image = image;
    else
        cv::cvtColor(image, gray_image, CV_BGR2GRAY);

    // reading the image into double *
    int rows = gray_image.rows;
    int cols = gray_image.cols;
    double * img_double;

    img_double = (double *)malloc(rows * cols * sizeof(double));
    for(int i=0; i<rows; i++) {
        for (int j = 0; j < cols; j++) {
            img_double[i+j*rows] = gray_image.at<uchar>(i, j);
        }
    }

    // line detection by lsd method
    int n;
    double * out;
    out = lsd(&n, img_double, rows, cols);

    for (int i = 0; i < n; i++)
    {
        double x1 = out[7 * i + 1];
        double y1 = out[7 * i + 0];
        double x2 = out[7 * i + 3];
        double y2 = out[7 * i + 2];

        double l = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
        if (l > length) {
            std::vector<double> line_temp(4); // 4 co-ordinates of 2 points
            line_temp[0] = x1;
            line_temp[1] = y1;
            line_temp[2] = x2;
            line_temp[3] = y2;

            lines.push_back(line_temp);
        }
    }

    // free memory
    free((void *)img_double);
    free((void *)out);
}

void LSD::LineDetectByCv(cv::Mat &image, std::vector<std::vector<double> > &lines, double length) {
    // implement by OpenCV
    cv::Mat gray_image;
    if (image.channels() == 1)
        gray_image = image;
    else
        cv::cvtColor(image, gray_image, CV_BGR2GRAY);

    std::vector<cv::Vec4d> lines_std;
    cv::Ptr<cv::LineSegmentDetector> lsd = cv::createLineSegmentDetector(cv::LSD_REFINE_STD);
    lsd->detect(gray_image, lines_std);

    for (int j = 0; j < lines_std.size(); ++j) {
        std::vector<double> tmp_line;
        for (int k = 0; k < 4; ++k) {
            tmp_line.push_back(lines_std[j][k]);
        }

        double l = sqrt(pow((tmp_line[0] - tmp_line[2]), 2.) + pow((tmp_line[1] - tmp_line[3]), 2.));
        if (l > length) {
            lines.push_back(tmp_line);
        }
    }
}