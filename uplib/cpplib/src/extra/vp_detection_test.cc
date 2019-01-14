/************************************************************
	> Author: ling
	> Mail: @mango.com
	> Created Time: 09/26/2018
************************************************************/
#include <glog/logging.h>

#include "vp_detection.h"
#include "util/timer.h"

using namespace cpplib;
using namespace colmap;
using namespace std;
using namespace cv;

void testVpDetection(string &image_path, bool b_show=false) {
    cv::Mat image = cv::imread(image_path);
    if(image.empty()){
        LOG(ERROR) << "map_ar_server_error||timestamp=" << GetTimeStamp() << "||"
                   << "server=location||"
                   << "type=1||"
                   << "msg=" << "cannot read image at path: " << image_path;
        return ;
    }

    // create DetectVP object
    DetectionVP detector(0.9999, 360);

    // using OpenCV LSD to detect line segment and get length of line segment greater than length_thresh
    double length_thresh = 30.0;
    std::vector<std::vector<double> > lines;
    detector.LineDetectionByLsd(image, lines, length_thresh);

    // set camera internal parameters, including Principle point (in pixel) and Focal length (in pixel)
    cv::Point2d principal_point(image.rows / 2, image.cols / 2);
    const float focal = 1007.46;

    // using slope to choose satisfied line segment
    std::vector<std::vector<double> > good_lines;
    detector.RemoveLines(lines, good_lines, 0.2, 5.0);

    // vanishing point detection
    std::vector<cv::Point3d> vps;
    std::vector<std::vector<int> > clusters;
    detector.GetVpsAndCluster(good_lines, principal_point, focal, vps, clusters);

    // using vanishing point to draw circle in image
    std::vector<std::vector<double> > vp_img;
    detector.GetPlaneVP(vps, vp_img);
    std::cout << "split point: " << int(vp_img[0][1]) << std::endl;

    // using line segment clusters to draw line in image
    if (b_show) {
        Scalar circle_color = cv::Scalar(0, 255, 0);
        circle(image, Point(int(vp_img[0][0]), int(vp_img[0][1])), 8, circle_color, -1);
        detector.DrawClusters(image, good_lines, clusters);
        imshow("vp_show", image);
        waitKey(0);
    }

    // split image by vanishing point
    int vp_split = (int(vp_img[0][1]) > image.rows / 10.) && (int(vp_img[0][1]) < image.rows) ?
                   int(vp_img[0][1]) : int(image.rows / 2.);
    cv::Rect roi(0, 0, image.cols, vp_split);
    image = image(roi);
    imwrite("/Users/didi/image_process/image_split.jpg", image);
}

int main() {
    string image_path = "/Users/didi/image_process/image.jpg";
    std::cout << "\n---------Start testing vanishing detection---------\n" << std::endl;
    testVpDetection(image_path, true);
}
