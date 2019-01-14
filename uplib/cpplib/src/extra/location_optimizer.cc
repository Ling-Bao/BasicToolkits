/************************************************************
	> Author: ling
	> Mail: @mango.com
	> Created Time: 09/14/2018
************************************************************/
#include <Poco/JSON/Parser.h>
#include <glog/logging.h>
#include <fstream>

#include "location_optimizer.h"
#include "util/timer.h"

using namespace cpplib;
using namespace colmap;
using Poco::DynamicStruct;
using Poco::JSON::Parser;
using Poco::JSON::Object;
using Poco::JSON::Array;

void LocationChecker::LoadConfig(const Object &object) {
    // Poco bug when not convert to string
    DynamicStruct fences_json = object;
    std::string fences_str = fences_json.toString();
    Parser parser;
    Object::Ptr object_ptr = parser.parse(fences_str).extract<Object::Ptr>();

    Array::Ptr fence_array = object_ptr->getArray("fences");
    for (const auto object: *fence_array) {
        Polygon polygon_fence;

        // polygon-fence
        Array::Ptr model_area_array = object.extract<Object::Ptr>()->getArray("polygon-fence");
        for (const auto var: *model_area_array) {
            double pos_x = var.extract<Object::Ptr>()->getValue<double>("pos_x");
            double pos_y = var.extract<Object::Ptr>()->getValue<double>("pos_y");
            double pos_z = var.extract<Object::Ptr>()->getValue<double>("pos_z");
            polygon_fence.polygon_points.emplace_back(pos_x, pos_y, pos_z);
        }

        polygon_fence.scene = object.extract<Object::Ptr>()->getValue<std::string>("scene");
        polygon_fence.region = object.extract<Object::Ptr>()->getValue<std::string>("region");

        polygon_fences.push_back(polygon_fence);
    }
}

void LocationChecker::LoadConfig(const std::string filename){

    std::ifstream fin(filename.c_str(), std::ios_base::in);
    if (!fin.is_open()) {
        LOG(WARNING) << "map_ar_location_checker_error||timestamp=" << GetTimeStamp() << "||"
                   << "message=" << "Polygon fences file load failed!";
        throw std::runtime_error("map_ar_location_checker_error: polygon fences file load failed!");
    }
    Parser parser;
    Object::Ptr object = parser.parse(fin).extract<Object::Ptr>();
    fin.close();
    LoadConfig(*object);
}

// The function will return true if the point x, y is inside the polygon fence, or
// false if it is not. If the point is exactly on the edge or vertex of the polygon,
// then the function may return true or false.
bool LocationChecker::RayCasting(const std::vector<Eigen::Vector3d> &polygon, const Eigen::Vector3d &point) {
    size_t size = polygon.size();
    if (size <= 2) {
        return false;
    }

    int j = size - 1;
    bool is_inside = false;

    for (size_t i = 0; i < size; i++) {
        if (((polygon[i](2) < point(2) && polygon[j](2) >= point(2)) ||
             (polygon[j](2) < point(2) && polygon[i](2) >= point(2)))
            && (polygon[i](0) <= point(0) || polygon[j](0) <= point(0))) {

            is_inside ^= (polygon[i](0) + (point(2) - polygon[i](2)) /
                                          (polygon[j](2) - polygon[i](2)) *
                                          (polygon[j](0) - polygon[i](0)) < point(0));
        }
        j = i;
    }

    return is_inside;
}

bool LocationChecker::CheckInPolygon(std::string &region, const Eigen::Vector3d &point) {
    bool in_polygon = false;
    for(const auto fence: polygon_fences) {
        in_polygon |= RayCasting(fence.polygon_points, point);
        if(in_polygon) {
            region = fence.region;
            break;
        }
    }

    return in_polygon;
}

void ImageProcess::SplitImageByROI(cv::Mat &img) {
    cv::Rect roi(0, 0, img.cols, int(img.rows / 2.));

    img = img(roi);
}

void ImageProcess::SplitImageByROI(cv::Mat &img, cv::Point2d principal_point, double focal) {
    // 1. get length of line segment greater than length_thresh
    std::vector<std::vector<double> > lines;
    double length_thresh = 30.0;
    detector.LineDetectionByLsd(img, lines, length_thresh);

    // 2. using slope to choose satisfied line segments
    std::vector<std::vector<double> > good_lines;
    detector.RemoveLines(lines, good_lines, 0.2, 5.0);

    // 3. get 3 orthogonal vanishing points
    std::vector<cv::Point3d> vps;
    detector.GetVps(good_lines, principal_point, focal, vps);

    // 4. get vanishing points in image
    std::vector<std::vector<double> > vp_img;
    detector.GetPlaneVP(vps, vp_img);

    // 5. get split point in image of height
    int vp_split = (int(vp_img[0][1]) > img.rows / 10.) && (int(vp_img[0][1]) < img.rows) ?
                                                                       int(vp_img[0][1]) : int(img.rows / 2.);

    // 6. split image by vanishing point
    cv::Rect roi(0, 0, img.cols, vp_split);
    img = img(roi);
}
