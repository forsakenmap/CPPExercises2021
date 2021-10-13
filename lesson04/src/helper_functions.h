#pragma once

#include <opencv2/highgui.hpp> // подключили часть библиотеки OpenCV, теперь мы можем работать с картинками (знаем про тип cv::Mat)

cv::Mat makeAllBlackPixelsBlue(cv::Mat image);

cv::Mat invertImageColors(cv::Mat image);

cv::Mat addBackgroundInsteadOfBlackPixels(cv::Mat object, cv::Mat background);

cv::Mat addBackgroundInsteadOfBlackPixelsLargeBackground(cv::Mat object, cv::Mat largeBackground);

cv::Mat addBackgroundInsteadOfBlackPixelsLargeBackgroundNTimes(cv::Mat object, cv::Mat largeBackground);

cv::Mat fillBackground(cv::Mat object, cv::Mat largeBackground);

cv::Mat addBackground(cv::Mat object, cv::Mat largeBackground, cv::Mat mask);

cv::Mat getBackgroundMask(cv::Mat object, cv::Vec3b color, double dis);

cv::Mat clearWithDSU(cv::Mat mask, char v, int min_size);

cv::Mat getBackgroundMask(cv::Mat object, cv::Mat back, double dis);

cv::Mat dilate(cv::Mat mask, int r);

cv::Mat erode(cv::Mat mask, int r);
