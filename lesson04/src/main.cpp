#include <iostream>
#include <filesystem>
#include <libutils/rasserts.h>

#include "disjoint_set.h"
#include "helper_functions.h"

#include <opencv2/highgui.hpp>

void testingMyDisjointSets() {
    DisjointSet set(5);
    rassert(set.count_differents() == 5, 2378923791);
    for (int element = 0; element < 5; ++element) {
        rassert(set.get_set(element) == element, 23892803643);
        rassert(set.get_set_size(element) == 1, 238928031);
    }
}

struct MyVideoContent4 {
    cv::Mat frame;
    cv::Vec3b color = cv::Vec3b(0,0,0);
    cv::Mat back;
};

void onMouseClick4(int event, int x, int y, int flags, void *pointerToMyVideoContent) {
    MyVideoContent4 &content = *((MyVideoContent4*) pointerToMyVideoContent);

    if (event == cv::EVENT_LBUTTONDOWN) {
        content.color = content.frame.at<cv::Vec3b>(y,x);
        content.back = content.frame.clone();
    }
}

void backgroundMagickStreaming() {
    cv::VideoCapture video(0);
    rassert(video.isOpened(), 3423948392481);

    MyVideoContent4 content;
    cv::Mat largeCastle = cv::imread("lesson03/data/castle_large.jpg");
    while (video.isOpened()) {
        bool isSuccess = video.read(content.frame);
        rassert(isSuccess, 348792347819);
        rassert(!content.frame.empty(), 3452314124643);
        cv::Mat res = getBackgroundMask(content.frame, content.color, 30);
        if(!content.back.empty())
            res = clearWithDSU(res, 1, 1);
        cv::imshow("video", addBackground(content.frame.clone(), largeCastle, res));
        cv::setMouseCallback("video", onMouseClick4, &content);

        int key = cv::waitKey(10);
        if(key == 32 || key == 27)
            break;
    }
}

int main() {
    try {
        //        testingMyDisjointSets();
        backgroundMagickStreaming();
        return 0;
    } catch (const std::exception &e) {
        std::cout << "Exception! " << e.what() << std::endl;
        return 1;
    }
}