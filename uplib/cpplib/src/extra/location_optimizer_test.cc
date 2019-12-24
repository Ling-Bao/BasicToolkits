/************************************************************
	> Author: ling
	> Mail: @mango.com
	> Created Time: 09/14/2018
************************************************************/
#include <glog/logging.h>

#include "location_optimizer.h"
#include "vp_detection.h"
#include "util/timer.h"

using namespace cpplib;
using namespace colmap;

void testLocationChecker() {
    LocationChecker loc_checker;
    bool b_use_split = true;

    std::vector<std::string> polygon_paths;
    polygon_paths.emplace_back("path-to/polygon_fences.json");
    polygon_paths.emplace_back("");

    for(auto &polygon_path : polygon_paths) {
        try {
            loc_checker.LoadConfig(polygon_path);
        }
        catch (std::runtime_error& e) {
            LOG(ERROR) << "Caught exception:\n" << e.what();
            b_use_split = false;
        }

        if (b_use_split) {
            Eigen::Vector3d loc_arkit_3d(-10.0, 0.0, -60.0);
            std::string region;
            assert(loc_checker.CheckInPolygon(region, loc_arkit_3d));
            std::cout << "Point is in polygon!" << std::endl;
        }
    }

    std::cout << "\n---------Check string compare---------" << std::endl;
    // Only for quickly testing for International Airport of T3 scene
    std::vector<std::string> model_names_test;
    model_names_test.emplace_back("");
    model_names_test.emplace_back("Model1");
    model_names_test.emplace_back("Model2");

    for(auto &model_name_test : model_names_test) {
        if (!model_name_test.compare("Model2")) {
            b_use_split = true;
        } else {
            b_use_split = false;
        }

        if (b_use_split) {
            std::cout << "Is T3 scene!" << std::endl;
        }
    }
}

bool testImageProcess() {
    std::string image_path = "path-to/image.jpg";
    cv::Mat img = cv::imread(image_path);
    cv::Mat img_ = img.clone();
    if(img.empty()){
        LOG(ERROR) << "map_ar_server_error||timestamp=" << GetTimeStamp() << "||"
                   << "server=location||"
                   << "type=1||"
                   << "msg=" << "cannot read image at path: " << image_path;
        return false;
    }

    std::cout << "\n---------Start testing split v1.0.0---------" << std::endl;
    std::cout << "Width: " << img.cols << "\tHeight: " << img.rows << std::endl;
    ImageProcess img_process;
    img_process.SplitImageByROI(img);
    cv::imwrite("/Users/didi/image_process/image_split.jpg", img);
    std::cout << "Width: " << img.cols << "\tHeight: " << img.rows << std::endl;

    std::cout << "\n---------Start testing split v2.0.0---------" << std::endl;
    std::cout << "Width: " << img_.cols << "\tHeight: " << img_.rows << std::endl;
    cv::Point2d principal_point(int(img.cols / 2.), int(img.rows / 2.));
    double focal = 1007.46;
    img_process.SplitImageByROI(img_, principal_point, focal);
    cv::imwrite("/Users/didi/image_process/image_split.jpg", img_);
    std::cout << "Width: " << img_.cols << "\tHeight: " << img_.rows << std::endl;

    return true;
}

int main(int argc, char** argv) {
    std::cout << "\n---------Start testing---------\n" << std::endl;
    std::cout << "\n---------LocationChecker testing---------" << std::endl;
    testLocationChecker();

    std::cout << "\n---------ImageProcess testing---------" << std::endl;
    testImageProcess();
    std::cout << "\n---------End testing---------\n" << std::endl;
}
