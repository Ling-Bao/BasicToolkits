/************************************************************
	> Author: ling
	> Mail: @mango.com
	> Created Time: 09/26/2018
************************************************************/
#ifndef CPPLIB_VP_DETECTION_H
#define CPPLIB_VP_DETECTION_H

extern "C"
{
#include "ext/LSD/lsd.h"
}

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>

namespace cpplib {

    class DetectionVP {
    public:
        struct LineInfo {
            LineInfo() {};

            cv::Mat_<double> param;
            double length;
            double orientation;
        };

        DetectionVP(double conf_coefficient, int nums_sampling_vp2, double outlier_ratio = 0.5);

        ~DetectionVP(void);

        // get 3 orthogonal vps
        void GetVps(std::vector<std::vector<double> > &lines, cv::Point2d principal_point,
                    double focal, std::vector<cv::Point3d> &vps);

        // get 3 orthogonal vps and its clusters
        void GetVpsAndCluster(std::vector<std::vector<double> > &lines, cv::Point2d principal_point,
                 double focal, std::vector<cv::Point3d> &vps, std::vector<std::vector<int> > &clusters);

        // get v1 by 2-line MSS and get vp hypothesis
        void GetVpHypoBy2Line(std::vector<std::vector<cv::Point3d> > &vp_hypo);

        // build sphere grid
        void GetSphereGrids(std::vector<std::vector<double> > &sphere_grid);

        // validate vp hypothesis
        void GetBestVpsHypo(std::vector<std::vector<cv::Point3d> > &vp_hypo,
                            std::vector<std::vector<double> > &sphere_grid, std::vector<cv::Point3d> &vps);

        // get clusters by vps (not necessary)
        void LinesClusterByVps(double angle_thresh, std::vector<cv::Point3d> &vps,
                               std::vector<std::vector<int> > &clusters);

        // get vp in image by vps
        void GetPlaneVP(std::vector<cv::Point3d> &vps, std::vector<std::vector<double> > &vp_img);

        // LSD line segment detection
        void LineDetectionByLsd(cv::Mat &image, std::vector<std::vector<double> > &lines, double length=30.0);

        void RemoveLines(std::vector<std::vector<double> > &lines, std::vector<std::vector<double> > &good_lines,
                         double down, double up);

        // for testing (not necessary)
        void DrawClusters(cv::Mat &img, std::vector<std::vector<double> > &lines,
                     std::vector<std::vector<int> > &clusters);

    private:
        double outlier_ratio;
        double conf_coefficient;
        int nums_sampling_vp2;

        cv::Point2d principal_point;
        double focal;

        std::vector<std::vector<double> > lines;
        std::vector<LineInfo> lines_info;
    };
}

#endif //CPPLIB_VP_DETECTION_H
