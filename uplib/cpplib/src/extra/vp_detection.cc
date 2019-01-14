/************************************************************
	> Author: ling
	> Mail: @mango.com
	> Created Time: 09/26/2018
************************************************************/
#include "vp_detection.h"
#include <iostream>

using namespace cpplib;

DetectionVP::DetectionVP(double conf_coefficient, int nums_sampling_vp2, double outlier_ratio) {
    this->outlier_ratio = outlier_ratio;
    this->conf_coefficient = conf_coefficient;
    this->nums_sampling_vp2 = nums_sampling_vp2;
}

DetectionVP::~DetectionVP(void) {

}

void DetectionVP::GetVps(std::vector<std::vector<double> > &lines, cv::Point2d principal_point, double focal,
                         std::vector<cv::Point3d> &vps) {
    this->lines = lines;
    this->principal_point = principal_point;
    this->focal = focal;

    // get vps hypotheses by 2-line MSS
    std::vector<std::vector<cv::Point3d> > vp_hypo;
    GetVpHypoBy2Line(vp_hypo);

    // get sphere grid
    std::vector<std::vector<double> > sphere_grid;
    GetSphereGrids(sphere_grid);

    // validate vps hypotheses
    GetBestVpsHypo(vp_hypo, sphere_grid, vps);
}

void DetectionVP::GetVpsAndCluster(std::vector<std::vector<double> > &lines, cv::Point2d principal_point, double focal,
                      std::vector<cv::Point3d> &vps, std::vector<std::vector<int> > &clusters) {
    this->lines = lines;
    this->principal_point = principal_point;
    this->focal = focal;

    // get vps hypotheses by 2-line MSS
    std::vector<std::vector<cv::Point3d> > vp_hypo;
    GetVpHypoBy2Line(vp_hypo);

    // get sphere grid
    std::vector<std::vector<double> > sphere_grid;
    GetSphereGrids(sphere_grid);

    // validate vps hypotheses
    GetBestVpsHypo(vp_hypo, sphere_grid, vps);

    // get line clusters by vps (not necessary)
    double angle_thresh = 6.0 / 180.0 * CV_PI;
    LinesClusterByVps(angle_thresh, vps, clusters);
}

void DetectionVP::GetVpHypoBy2Line(std::vector<std::vector<cv::Point3d> > &vp_hypo) {
    // compute iterations by outlier ratio and confidence coefficient
    double prob = 1.0 / 3.0 * pow(1.0 - outlier_ratio, 2.0);
    int iterate_nums = int(log(1 - conf_coefficient) / log(1.0 - prob));

    // save lines info to lines_info
    double step_vp2 = 2.0 * CV_PI / nums_sampling_vp2;
    int line_nums = int(lines.size());
    lines_info.resize(line_nums);
    for (int i = 0; i < line_nums; ++i) {
        cv::Mat_<double> p1 = (cv::Mat_<double>(3, 1) << lines[i][0], lines[i][1], 1.0);
        cv::Mat_<double> p2 = (cv::Mat_<double>(3, 1) << lines[i][2], lines[i][3], 1.0);

        // get line's parameters of a, b, c
        lines_info[i].param = p1.cross(p2);

        double dx = lines[i][0] - lines[i][2];
        double dy = lines[i][1] - lines[i][3];
        lines_info[i].length = sqrt(dx * dx + dy * dy);
        if (atan2(dy, dx) < 0) {
            lines_info[i].orientation += CV_PI;
        }
    }

    // get vp hypothesis
    vp_hypo = std::vector<std::vector<cv::Point3d> >(iterate_nums * nums_sampling_vp2, std::vector<cv::Point3d>(3));
    int count = 0;
    srand((unsigned) time(NULL));
    for (int i = 0; i < iterate_nums; ++i) {
        // get v1 by using 2-lines MSS
        unsigned long idx1 = rand() % line_nums;
        unsigned long idx2 = rand() % line_nums;
        while (idx2 == idx1) {
            idx2 = rand() % line_nums;
        }

        cv::Mat_<double> vp1_img = lines_info[idx1].param.cross(lines_info[idx2].param);
        if (vp1_img(2) == 0) {
            i--;
            continue;
        }

        cv::Mat_<double> vp1 = (cv::Mat_<double>(3, 1) << vp1_img(0) / vp1_img(2) - principal_point.x,
        vp1_img(1) / vp1_img(2) - principal_point.y, focal);

        if (vp1(2) == 0) { vp1(2) = 0.0011; }
        double N = sqrt(vp1(0) * vp1(0) + vp1(1) * vp1(1) + vp1(2) * vp1(2));
        vp1 *= 1.0 / N;

        // get vp2 and vp3
        cv::Mat_<double> vp2 = (cv::Mat_<double>(3, 1) << 0.0, 0.0, 0.0);
        cv::Mat_<double> vp3 = (cv::Mat_<double>(3, 1) << 0.0, 0.0, 0.0);
        for (int j = 0; j < nums_sampling_vp2; ++j) {
            // get vp2
            double lambda = j * step_vp2;

            // phi is solution of Eq.(6) and Eq.(7)
            double k1 = vp1(0) * sin(lambda) + vp1(1) * cos(lambda);
            double k2 = vp1(2);
            double phi = atan(-k2 / k1);

            double Z = cos(phi);
            double X = sin(phi) * sin(lambda);
            double Y = sin(phi) * cos(lambda);

            vp2(0) = X;
            vp2(1) = Y;
            vp2(2) = Z;
            if (vp2(2) == 0.0) { vp2(2) = 0.0011; }
            N = sqrt(vp2(0) * vp2(0) + vp2(1) * vp2(1) + vp2(2) * vp2(2));
            vp2 *= 1.0 / N;
            if (vp2(2) < 0) { vp2 *= -1.0; }

            // get vp3 by vp1 cross vp2
            vp3 = vp1.cross(vp2);
            if (vp3(2) == 0.0) { vp3(2) = 0.0011; }
            N = sqrt(vp3(0) * vp3(0) + vp3(1) * vp3(1) + vp3(2) * vp3(2));
            vp3 *= 1.0 / N;
            if (vp3(2) < 0) { vp3 *= -1.0; }

            vp_hypo[count][0] = cv::Point3d(vp1(0), vp1(1), vp1(2));
            vp_hypo[count][1] = cv::Point3d(vp2(0), vp2(1), vp2(2));
            vp_hypo[count][2] = cv::Point3d(vp3(0), vp3(1), vp3(2));

            count++;
        }
    }
}

void DetectionVP::GetSphereGrids(std::vector<std::vector<double> > &sphere_grid) {
    // build sphere grid with 1 degree accuracy
    double angel_accuracy = 1.0 / 180.0 * CV_PI;
    double angle_span_la = CV_PI / 2.0;
    double angle_span_lo = CV_PI * 2.0;
    int grid_la = int(angle_span_la / angel_accuracy);
    int grid_lo = int(angle_span_lo / angel_accuracy);

    // using zero to initialize sphere grid cell
    sphere_grid = std::vector<std::vector<double> >(grid_la, std::vector<double>(grid_lo));
    for (int i = 0; i < grid_la; ++i) {
        for (int j = 0; j < grid_lo; ++j) {
            sphere_grid[i][j] = 0.0;
        }
    }

    // put intersection points into the grid
    double angel_tolerance = 60.0 / 180.0 * CV_PI;
    cv::Mat_<double> pt_intersect;
    double x = 0.0, y = 0.0;
    double X = 0.0, Y = 0.0, Z = 0.0, N = 0.0;
    double latitude = 0.0, longitude = 0.0;
    int LA = 0, LO = 0;
    double angle_dev = 0.0;
    for (int i = 0; i < int(lines.size()); ++i) {
        for (int j = i + 1; j < int(lines.size()); ++j) {
            // get intersect point
            pt_intersect = lines_info[i].param.cross(lines_info[j].param);
            if (pt_intersect(2, 0) == 0) {
                continue;
            }
            x = pt_intersect(0, 0) / pt_intersect(2, 0);
            y = pt_intersect(1, 0) / pt_intersect(2, 0);

            X = x - principal_point.x;
            Y = y - principal_point.y;
            Z = focal;
            N = sqrt(X * X + Y * Y + Z * Z);
            latitude = acos(Z / N);
            longitude = atan2(X, Y) + CV_PI;

            LA = int(latitude / angel_accuracy);
            if (LA >= grid_la) {
                LA = grid_la - 1;
            }

            LO = int(longitude / angel_accuracy);
            if (LO >= grid_lo) {
                LO = grid_lo - 1;
            }

            angle_dev = abs(lines_info[i].orientation - lines_info[j].orientation);
            angle_dev = std::min(CV_PI - angle_dev, angle_dev);
            if (angle_dev > angel_tolerance) {
                continue;
            }

            sphere_grid[LA][LO] += sqrt(lines_info[i].length * lines_info[j].length) *
                                   (sin(2.0 * angle_dev) + 0.2); // 0.2 is much robuster
        }
    }

    // gaussian smoothing
    int half_size = 1;
    int win_size = half_size * 2 + 1;
    int neighbor_num = win_size * win_size;
    std::vector<std::vector<double> > sphere_grid_new = std::vector<std::vector<double> >(grid_la,
                                                                                          std::vector<double>(grid_lo));
    for (int i = half_size; i < grid_la - half_size; ++i) {
        for (int j = half_size; j < grid_lo - half_size; ++j) {
            double neighbor_total = 0.0;
            for (int m = 0; m < win_size; ++m) {
                for (int n = 0; n < win_size; ++n) {
                    neighbor_total += sphere_grid[i - half_size + m][j - half_size + n];
                }
            }

            sphere_grid_new[i][j] = sphere_grid[i][j] + neighbor_total / neighbor_num;
        }
    }
    sphere_grid = sphere_grid_new;
}

void DetectionVP::GetBestVpsHypo(std::vector<std::vector<cv::Point3d> > &vp_hypo,
                                 std::vector<std::vector<double> > &sphere_grid, std::vector<cv::Point3d> &vps) {
    int num = vp_hypo.size();
    double one_degree = 1.0 / 180.0 * CV_PI;

    // get the corresponding line length of every hypotheses
    std::vector<double> line_length(num, 0.0);
    for (int i = 0; i < num; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (vp_hypo[i][j].z == 0.0) {
                continue;
            }

            if (vp_hypo[i][j].z > 1.0 || vp_hypo[i][j].z < -1.0) {
                std::cout << 1.0000 << std::endl;
            }

            double latitude = acos(vp_hypo[i][j].z);
            double longitude = atan2(vp_hypo[i][j].x, vp_hypo[i][j].y) + CV_PI;

            int grid_la = int(latitude / one_degree);
            if (grid_la == 90) {
                grid_la = 89;
            }

            int grid_lo = int(longitude / one_degree);
            if (grid_lo == 360) {
                grid_lo = 359;
            }

            line_length[i] += sphere_grid[grid_la][grid_lo];
        }
    }

    // get the best hypotheses
    int best_idx = 0;
    double max_length = 0.0;
    for (int i = 0; i < num; ++i) {
        if (line_length[i] > max_length) {
            max_length = line_length[i];
            best_idx = i;
        }
    }

    vps = vp_hypo[best_idx];
}

void DetectionVP::LinesClusterByVps(double angle_thresh, std::vector<cv::Point3d> &vps,
                                    std::vector<std::vector<int> > &clusters) {
    clusters.clear();
    clusters.resize(3);

    // get the corresponding vanish points in the image plane
    std::vector<cv::Point2d> vp_img(3);
    for (int i = 0; i < 3; ++i) {
        vp_img[i].x = vps[i].x * focal / vps[i].z + principal_point.x;
        vp_img[i].y = vps[i].y * focal / vps[i].z + principal_point.y;
    }

    for (int i = 0; i < int(lines.size()); ++i) {
        double x1 = lines[i][0];
        double y1 = lines[i][1];
        double x2 = lines[i][2];
        double y2 = lines[i][3];
        double xm = (x1 + x2) / 2.0;
        double ym = (y1 + y2) / 2.0;

        double v1x = x1 - x2;
        double v1y = y1 - y2;
        double N1 = sqrt(v1x * v1x + v1y * v1y);
        v1x /= N1;
        v1y /= N1;

        double min_angle = 1000.0;
        int best_idx = 0;
        for (int j = 0; j < 3; ++j) {
            double v2x = vp_img[j].x - xm;
            double v2y = vp_img[j].y - ym;
            double N2 = sqrt(v2x * v2x + v2y * v2y);
            v2x /= N2;
            v2y /= N2;

            double cross_value = v1x * v2x + v1y * v2y;
            if (cross_value > 1.0) {
                cross_value = 1.0;
            }
            if (cross_value < -1.0) {
                cross_value = -1.0;
            }
            double angle = acos(cross_value);
            angle = std::min(CV_PI - angle, angle);

            if (angle < min_angle) {
                min_angle = angle;
                best_idx = j;
            }
        }

        if (min_angle < angle_thresh) {
            clusters[best_idx].push_back(i);
        }
    }
}

void DetectionVP::GetPlaneVP(std::vector<cv::Point3d> &vps, std::vector<std::vector<double> > &vp_img) {
    // get the corresponding vanish points in the image plane
    for (int i = 0; i < int(vps.size()); ++i) {
        std::vector<double> vp;

        vp.push_back(vps[i].x * focal / vps[i].z + principal_point.x);
        vp.push_back(vps[i].y * focal / vps[i].z + principal_point.y);
        vp_img.push_back(vp);
    }
}

void DetectionVP::LineDetectionByLsd(cv::Mat &image, std::vector<std::vector<double> > &lines, double length) {
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

    // implement by OpenCV
//    cv::Mat gray_image;
//    if (image.channels() == 1)
//        gray_image = image;
//    else
//        cv::cvtColor(image, gray_image, CV_BGR2GRAY);
//
//    std::vector<cv::Vec4d> lines_std;
//    cv::Ptr<cv::LineSegmentDetector> lsd = cv::createLineSegmentDetector(cv::LSD_REFINE_STD);
//    lsd->detect(gray_image, lines_std);
//
//    for (int j = 0; j < lines_std.size(); ++j) {
//        std::vector<double> tmp_line;
//        for (int k = 0; k < 4; ++k) {
//            tmp_line.push_back(lines_std[j][k]);
//        }
//
//        double l = sqrt(pow((tmp_line[0] - tmp_line[2]), 2.) + pow((tmp_line[1] - tmp_line[3]), 2.));
//        if (l > length) {
//            lines.push_back(tmp_line);
//        }
//    }
}

void DetectionVP::RemoveLines(std::vector<std::vector<double> > &lines, std::vector<std::vector<double> > &good_lines,
                              double down, double up) {
    for (int idx = 0; idx < int(lines.size()); ++idx) {
        double k = fabs((lines[idx][1] - lines[idx][3]) / (lines[idx][0] - lines[idx][2]));

        std::vector<double> line;
        if ((k > down) && (k < up)) {
            for (int j = 0; j < 4; ++j) {
                line.push_back(lines[idx][j]);
            }
            good_lines.push_back(line);
        }
    }
}

void DetectionVP::DrawClusters(cv::Mat &img, std::vector<std::vector<double> > &lines,
                               std::vector<std::vector<int> > &clusters) {
    std::vector<cv::Scalar> lineColors(3);
    lineColors[0] = cv::Scalar(0, 0, 255);
    lineColors[1] = cv::Scalar(0, 255, 0);
    lineColors[2] = cv::Scalar(255, 0, 0);

    for (int i = 0; i < int(lines.size()); ++i) {
        int idx = i;
        cv::Point pt_s = cv::Point(lines[idx][0], lines[idx][1]);
        cv::Point pt_e = cv::Point(lines[idx][2], lines[idx][3]);

        cv::line(img, pt_s, pt_e, cv::Scalar(0, 0, 0), 2, CV_AA);
    }

    for (int i = 0; i < int(clusters.size()); ++i) {
        for (int j = 0; j < int(clusters[i].size()); ++j) {
            int idx = clusters[i][j];

            cv::Point pt_s = cv::Point(lines[idx][0], lines[idx][1]);
            cv::Point pt_e = cv::Point(lines[idx][2], lines[idx][3]);

            cv::line(img, pt_s, pt_e, lineColors[i], 2, CV_AA);
        }
    }
}