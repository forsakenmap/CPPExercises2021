#include "blur.h"
#include <math.h>
#include <libutils/rasserts.h>
double pi = 3.14159265359;
cv::Mat blur(cv::Mat img, double sigma) {
    // вычислим среднеквадратичное отклонение, пусть сигма это размер матрицы +- от центрального пикселя (квадрат берём 3*3 5*5 итд)
    // среднее арифметическое
        cv::Mat img1 = img.clone();
    for(int x = sigma-1; x < img.cols-sigma+1; x++) {
        for(int y = sigma-1; y < img.rows-sigma+1; y++) {
            double sumr, colr;
            colr = 0;
            sumr = 0;
            double sumg, colg;
            colg = 0;
            sumg = 0;
            double sumb, colb;
            colb = 0;
            sumb = 0;
            for(int i = x - sigma; i <= x + sigma; i++) {
                for(int j = y - sigma; j <= y + sigma; j++) {
                    cv::Vec3b c = img.at<cv::Vec3b>(i, j);
                    int r = c[2];
                    colr++;
                    sumr += r;
                    int g = c[1];
                    colg++;
                    sumg += g;
                    int b = c[0];
                    colb++;
                    sumb += b;
                }
            }
            sumb /= colb;
            sumr /= colr;
            sumg /= colg;
            double kvg = 0;
            double kvb = 0;
            double kvr = 0;
            for(int i = x - sigma; i <= x + sigma; i++) {
                for(int j = y - sigma; j <= y + sigma; j++) {
                    cv::Vec3b c = img.at<cv::Vec3b>(i, j);
                    int r = c[2];
                    kvr += (sumr - r)*(sumr - r);
                    int g = c[1];
                    kvg += (sumg - g)*(sumg - g);
                    int b = c[0];
                    kvb += (sumb - b)*(sumb - b);
                }
            }
            kvr /= colr;
            kvg /= colg;
            kvb /= colb;
            unsigned int r = (1/(2*pi*kvr*kvr))*exp(-(x*x+y*y)/(2*kvr*kvr));
            unsigned int g = (1/(2*pi*kvg*kvg))*exp(-(x*x+y*y)/(2*kvg*kvg));
           unsigned int b = (1/(2*pi*kvb*kvb))*exp(-(x*x+y*y)/(2*kvb*kvb));
            img1.at<cv::Vec3b>(x, y) = cv::Vec3b(b,g,r);
        }
    }
    // TODO формулу весов можно найти тут:
    // https://ru.wikipedia.org/wiki/%D0%A0%D0%B0%D0%B7%D0%BC%D1%8B%D1%82%D0%B8%D0%B5_%D0%BF%D0%BE_%D0%93%D0%B0%D1%83%D1%81%D1%81%D1%83
    return img1;
}
