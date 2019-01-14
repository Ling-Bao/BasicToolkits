/************************************************************
	> Author: ling
	> Mail: @mango.com
	> Created Time: 09/14/2018
************************************************************/
#ifndef CPPLIB_SPLIT_QUERY_H
#define CPPLIB_SPLIT_QUERY_H

#include <string>
#include <vector>
#include <Eigen/Dense>
#include <Poco/JSON/Object.h>
#include <opencv2/opencv.hpp>

#include "vp_detection.h"

namespace cpplib {

    class LocationChecker {
    public:
        struct Polygon {
            Polygon() {};

            std::string scene;
            std::string region;

            std::vector<Eigen::Vector3d> polygon_points;
        };

        // load pickup polygon fence
        void LoadConfig(const std::string filename);

        void LoadConfig(const Poco::JSON::Object &object);

        // check 2Dpoint in polygon
        bool RayCasting(const std::vector<Eigen::Vector3d> &polygon, const Eigen::Vector3d &point);

        bool CheckInPolygon(std::string &region, const Eigen::Vector3d &point);

    private:
        std::vector<Polygon> polygon_fences;
    };

    class ImageProcess {
    public:
        // v1.0.0: split by fixed value, discard
        void SplitImageByROI(cv::Mat &img);

        // v2.0.0: split by vanishing point
        void SplitImageByROI(cv::Mat &img, cv::Point2d principal_point, double focal);

    private:
        // conf_coefficient=0.9999, nums_sampling_vp2=360 is experiment value
        DetectionVP detector = DetectionVP(0.9999, 360);
    };
}

#endif //CPPLIB_SPLIT_QUERY_H
