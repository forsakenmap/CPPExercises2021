#pragma once

#include <opencv2/highgui.hpp>

cv::Mat blur(cv::Mat img, double sigma, int r);
double G(int dx, int dy, double s);
