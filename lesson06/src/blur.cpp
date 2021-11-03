#include "blur.h"
#define _USE_MATH_DEFINES
#include <math.h>

cv::Mat blur(cv::Mat img, double s, int r) {
    cv::Mat ks(2*r + 1, 2*r + 1, CV_64F);
    for(int di = 0; di < ks.rows; di++)
        for(int dj = 0; dj < ks.cols; dj++)
            ks.at<double>(di, dj) = G(di-r, dj-r, s);
    cv::Mat res = img.clone();
    for(int i = 0; i < res.rows; i++) {
        for (int j = 0; j < res.cols; j++) {
            cv::Vec3d value(0,0,0);
            double k1 = 0;
            for(int di = -r; di <= r; di++)
                for(int dj = -r; dj <= r; dj++){
                    if(i+di < 0 || i+di >= res.rows || j+dj < 0 || j+dj >= res.cols)
                        continue;
                    double k = ks.at<double>(di+r, dj+r);
                    cv::Vec3b c = img.at<cv::Vec3b>(i+di, j+dj);
                    value += c*k;
                    k1 += k;
                }
            value /= k1;
            res.at<cv::Vec3b>(i, j) = value;
        }
    }
    return res;
}

double G(int dx, int dy, double s){
    return exp(-(dx*dx+dy*dy)/(2*s*s))/(2*M_PI*s*s);
}
