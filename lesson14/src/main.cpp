#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/calib3d/calib3d.hpp>

#include <chrono>
#include <iostream>
#include <filesystem>
#include <memory>

#include <libutils/rasserts.h>


void drawText(cv::Mat img, std::string text, double fontScale, int &yOffset) {
    cv::Scalar white(255, 255, 255);
    // рассчитываем высоту текста в пикселях:
    float textHeight = cv::getTextSize(text, cv::FONT_HERSHEY_DUPLEX, fontScale, 1, nullptr).height;
    yOffset += textHeight; // увеличиваем сдвиг на высоту текста в пикселях
    cv::putText(img, text, cv::Point(0, yOffset), cv::FONT_HERSHEY_DUPLEX, fontScale, white);
}


void run() {
    const bool uWc = false;
    bool drawOver = true; // рисовать ли поверх наложенную картинку (можно включить-включить чтобы мигнуть картинкой и проверить качество выравнивания)
    bool drawDebug = true; // рисовать ли поверх отладочную информацию (например красный кант вокруг нарисованной поверх картинки)
    bool useSIFTDescriptor = false; // SIFT работает довольно медленно, попробуйте использовать ORB + не забудьте что тогда вам нужен другой DescriptorMatcher
    cv::Mat imgFrame, imgForDetection, imgToDraw;
    // если у вас не работает через веб. камеру - будут использоваться заготовленные картинки
    imgFrame = cv::imread(
            "lesson14/data/1_box2/box0.png"); // пример кадра с вебкамеры, на нем мы хотим найти объект и вместо него нарисовать другую картинку
    imgForDetection = cv::imread(
            "lesson14/data/1_box2/box1.png"); // пример картинки которую мы хотим найти на видеокадре
    imgToDraw = cv::imread(
            "lesson14/data/1_box2/box1_nesquik.png"); // пример картинки которую мы хотим нарисовать заместо искомой
    rassert(!imgFrame.empty(), 324789374290023);
    rassert(!imgForDetection.empty(), 3789572984290019);
    rassert(!imgToDraw.empty(), 3789572984290021);

    std::shared_ptr<cv::VideoCapture> video;
    if (uWc) {
        std::cout << "Trying to open web camera..." << std::endl;
        video = std::make_shared<cv::VideoCapture>(0);
        rassert(video->isOpened(), 3482789346289027);
        std::cout << "Web camera video stream opened." << std::endl;
    }

    while (true) {
        cv::Mat currentFrame; // текущий кадр с веб. камеры
        if (uWc) {
            bool isSuccess = video->read(currentFrame);
            rassert(isSuccess, 347283947290039);
            rassert(!currentFrame.empty(), 347283947290040);
        } else {
            currentFrame = imgFrame; // или если у вас не работает OpenCV с веб. камерой - то пусть хотя бы картинка-пример используется
        }
        auto frameProcessingStartTime = std::chrono::steady_clock::now(); // замеряем сколько сейчас времени чтобы оценить FPS
        auto frameFilteringStartTime = std::chrono::steady_clock::now();
        auto frameMatchingStartTime = std::chrono::steady_clock::now();
        cv::Mat mainWindowImage = currentFrame.clone(); // делаем копию чтобы на ней рисовать любую отладочную информацию не портя оригинальную картинку
        {
            // TODO сопоставьте две картинки: currentFrame и imgForDetection, затем нарисуйте imgToDraw в соответствии с матрицей Гомографии
            cv::Ptr<cv::FeatureDetector> detector;
            cv::Ptr<cv::DescriptorMatcher> matcher;
            if (useSIFTDescriptor) {
                detector = cv::SIFT::create();
                matcher = cv::DescriptorMatcher::create(cv::DescriptorMatcher::FLANNBASED);
            } else {
                detector = cv::ORB::create();
                matcher = cv::DescriptorMatcher::create(cv::DescriptorMatcher::BRUTEFORCE);
                // TODO SIFT работает довольно медленно, попробуйте использовать ORB + не забудьте что тогда вам нужен другой DescriptorMatcher

                // TODO кроме того будет быстрее работать если вы будете использовать релизную сборку вместо Debug:
                // см. "Как ускорить программу" - https://www.polarnick.com/blogs/239/2021/school239_11_2021_2022/2021/10/05/lesson5-disjoint-set.html
            }
            std::vector<cv::KeyPoint> keypoints0, keypoints1; // здесь будет храниться список ключевых точек
            cv::Mat descriptors0, descriptors1;
            detector->detectAndCompute(currentFrame, cv::noArray(), keypoints0, descriptors0);
            detector->detectAndCompute(imgForDetection, cv::noArray(), keypoints1, descriptors1);
            std::cout << "Keypoints initially: " << keypoints0.size() << ", " << keypoints1.size() << "..."
                      << std::endl;
            frameMatchingStartTime = std::chrono::steady_clock::now();
            std::vector<std::vector<cv::DMatch>> matches01;
            matcher->knnMatch(descriptors0, descriptors1, matches01, 2);
            std::vector<std::vector<cv::DMatch>> matches10;
            matcher->knnMatch(descriptors1, descriptors0, matches10, 2);
            std::vector<double> distances01;
            for (auto &i : matches01) {
                distances01.push_back(i[0].distance);
            }
            std::sort(distances01.begin(), distances01.end());
            std::vector<double> distances10;
            for (auto &i : matches10) {
                distances10.push_back(i[0].distance);
            }
            std::sort(distances10.begin(), distances10.end());
            frameFilteringStartTime = std::chrono::steady_clock::now();
            std::vector<cv::Point2f> points0;
            std::vector<cv::Point2f> points1;
            for (int i = 0; i < keypoints0.size(); ++i) {
                cv::DMatch match = matches01[i][0];
                rassert(match.queryIdx == i,
                        234782749278097);
                int j = match.trainIdx;
                rassert(j < keypoints1.size(),
                        38472957238099);
                if (match.distance > distances01[distances01.size() / 2]) {
                    continue;
                }
                cv::DMatch match2 = matches01[i][1];
                if (match.distance > 0.7 * match2.distance) {
                    continue;
                }
                cv::DMatch match01 = match;
                cv::DMatch match10 = matches10[match01.trainIdx][0];
                if (match10.trainIdx != i) {
                    continue;
                }
                points0.push_back(keypoints0[i].pt);
                points1.push_back(keypoints1[j].pt);
            }
            rassert(points0.size() == points1.size(), 234723947289089);
            std::cout << points0.size() << "/" << keypoints0.size() << " good matches left" << std::endl;

            // TODO findHomography(...) + рисование поверх:
            const double ransacReprojThreshold = 3.0;
            std::vector<unsigned char> inliersMask;
            cv::Mat H01;
            if (points0.size() > 10)
                H01 = cv::findHomography(points0, points1, cv::RANSAC, ransacReprojThreshold, inliersMask);
            if (points0.size() <= 10 || H01.empty()) {
                // см. документацию https://docs.opencv.org/4.5.1/d9/d0c/group__calib3d.html#ga4abc2ece9fab9398f2e560d53c8c9780
                // "Note that whenever an H matrix cannot be estimated, an empty one will be returned."
                std::cout << "FAIL 24123422!" << std::endl;
            } else {
                cv::Mat overlapImg = imgToDraw.clone();
                if (drawDebug) {
                    // рисуем красный край у накладываемой картинки
                    cv::Scalar red(0, 0, 255);
                    cv::rectangle(overlapImg, cv::Point(0, 0), cv::Point(overlapImg.cols - 1, overlapImg.rows - 1), red,
                                  2);
                }
                if (drawOver) {
                    cv::Mat H10 = H01.inv(); // у матрицы есть обратная матрица - находим ее, какое преобразование она делает?
                    cv::warpPerspective(overlapImg, mainWindowImage, H10, mainWindowImage.size(), cv::INTER_LINEAR,
                                        cv::BORDER_TRANSPARENT);
                }
            }
        }

        if (drawDebug) {
            int t = 0;
            auto frameProcessingEndTime = std::chrono::steady_clock::now();
            int timeForFrame = std::chrono::duration_cast<std::chrono::milliseconds>(
                    frameProcessingEndTime - frameProcessingStartTime).count();
            int timeForFiltering = std::chrono::duration_cast<std::chrono::milliseconds>(
                    frameProcessingEndTime - frameFilteringStartTime).count();
            int timeForMatching = std::chrono::duration_cast<std::chrono::milliseconds>(
                    frameFilteringStartTime - frameMatchingStartTime).count();
            int timeForDetecting = std::chrono::duration_cast<std::chrono::milliseconds>(
                    frameMatchingStartTime - frameProcessingStartTime).count();
            int fps;
            if (timeForFrame == 0) {
                fps = 1001;
            } else {
                fps = (int) std::round(1000.0 / timeForFrame);
            }
            drawText(mainWindowImage, std::to_string(fps) + " FPS", 0.5, t);

            // TODO добавьте короткую справку про кнопки управления
            drawText(mainWindowImage, "1 - change detecting image, 2 - change replacing image", 0.5, t);
            drawText(mainWindowImage, "3 - enable/disable debug info, S - change method(SIFT(slow)/ORB(fast))", 0.5,
                     t);
            drawText(mainWindowImage, "H - enable/disable overlay", 0.5, t);
            drawText(mainWindowImage,
                     "Time: " + std::to_string(timeForFrame) + " ms = " + std::to_string(timeForDetecting) +
                     " ms detect + " + std::to_string(timeForMatching) + " ms match + "
                     + std::to_string(timeForFiltering) + " ms filter",
                     0.5, t);
        }

        // Рисуем все три окошка:
        cv::imshow("Frame", mainWindowImage);
        cv::imshow("Image for detection", imgForDetection);
        cv::imshow("Image to draw", imgToDraw);

        // Смотрим нажал ли пользователь какую-нибудь кнопку
        int key = cv::waitKey(
                10); // число в скобочках - максимальное число миллисекунд которые мы ждем кнопки от пользователя, а иначе - считаем что ничего не нажато
        if (key == -1) {
            // прошло 5 миллисекунд но ничего не было нажато - значит идем обрабатывать следующий кадр с веб. камеры
        } else if (key == 27) { // Esc - выключаем программу
            break;
        } else if (uWc && key == 49) {
            imgForDetection = currentFrame.clone();
        } else if (uWc && key == 50) {
            imgToDraw = currentFrame.clone();
        } else if (key == 104) {
            drawOver = !drawOver;
        } else if (key == 51) {
            drawDebug = !drawDebug;
        } else if (key == 115) {
            useSIFTDescriptor = !useSIFTDescriptor;
        } else {
            std::cerr << "UNKNOWN KEY " << key << " WAS PRESSED" << std::endl;
        }
    }
}


int main() {
    while (true) {
        try {
            run();
            return 0;
        } catch (const std::exception &e) {
            std::cout << "Exception! " << e.what() << std::endl;
            std::cout << "Restart" << std::endl;
            return 1;
        }
    }
}