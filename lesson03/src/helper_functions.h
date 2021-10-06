#pragma once

#include <opencv2/highgui.hpp> // подключили часть библиотеки OpenCV, теперь мы можем работать с картинками (знаем про тип cv::Mat)

cv::Mat makeAllBlackPixelsBlue(cv::Mat image);

cv::Mat blc(cv::Mat image);

cv::Mat invertImageColors(cv::Mat image);

cv::Mat addBackgroundInsteadOfBlackPixels(cv::Mat object, cv::Mat background);

cv::Mat addBackgroundInsteadOfBlackPixelsLargeBackground(cv::Mat object, cv::Mat largeBackground);

cv::Mat bg(cv::Mat object, cv::Mat largeBackground, int n);

cv::Mat kl(cv::Mat obj, cv::Mat lbg);

cv::Mat tored(std::vector<int>, std::vector<int>, cv::Mat);

cv::Mat resize(cv::Mat, int, int);

cv::Mat addbgred(cv::Mat object, cv::Mat background, std::vector<int>, std::vector<int>);
