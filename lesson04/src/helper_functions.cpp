#include "helper_functions.h"
#include "disjoint_set.h"

#include <libutils/rasserts.h>
#include <iostream>


cv::Mat makeAllBlackPixelsBlue(cv::Mat image) {
    // реализуйте функцию которая каждый черный пиксель картинки сделает синим

    // ниже приведен пример как узнать цвет отдельного пикселя - состоящий из тройки чисел BGR (Blue Green Red)
    // чем больше значение одного из трех чисел - тем насыщеннее его оттенок
    // всего их диапазон значений - от 0 до 255 включительно
    // т.е. один байт, поэтому мы используем ниже тип unsigned char - целое однобайтовое неотрицательное число
    for(int i = 0; i < image.rows; i++) {
        for(int j = 0; j < image.cols; j++) {
            cv::Vec3b color = image.at<cv::Vec3b>(i,
                                                  j); // взяли и узнали что за цвет в пикселе в 14-ом ряду (т.к. индексация с нуля) и 6-ой колонке
            unsigned char blue = color[0]; // если это число равно 255 - в пикселе много синего, если равно 0 - в пикселе нет синего
            unsigned char green = color[1];
            unsigned char red = color[2];

            // как получить белый цвет? как получить черный цвет? как получить желтый цвет?
            // поэкспериментируйте! например можете всю картинку заполнить каким-то одним цветом

            // пример как заменить цвет по тем же координатам
            if (blue == 0 && green == 0 && red == 0)
                blue = 0xff;
            // запустите эту версию функции и посмотрите на получившуюся картинку - lesson03/resultsData/01_blue_unicorn.jpg
            // какой пиксель изменился? почему он не чисто красный?
            image.at<cv::Vec3b>(i, j) = cv::Vec3b(blue, green, red);

        }
    }
    return image;
}

cv::Mat invertImageColors(cv::Mat image) {
    // реализуйте функцию которая каждый цвет картинки инвертирует:
    // т.е. пусть ночь станет днем, а сумрак рассеется
    // иначе говоря замените каждое значение яркости x на (255-x) (т.к находится в диапазоне от 0 до 255)
    for(int i = 0; i < image.rows; i++) {
        for(int j = 0; j < image.cols; j++) {
            cv::Vec3b color = image.at<cv::Vec3b>(i,
                                                  j);
            unsigned char blue = color[0];
            unsigned char green = color[1];
            unsigned char red = color[2];
            image.at<cv::Vec3b>(i, j) = cv::Vec3b(0xff-blue, 0xff-green, 0xff-red);

        }
    }
    return image;
}

cv::Mat addBackgroundInsteadOfBlackPixels(cv::Mat object, cv::Mat background) {
    // реализуйте функцию которая все черные пиксели картинки-объекта заменяет на пиксели с картинки-фона

    rassert(object.cols == background.cols, 341241251251351);
    rassert(object.rows == background.rows, 341241251251351);

    for(int i = 0; i < object.rows; i++) {
        for(int j = 0; j < object.cols; j++) {
            cv::Vec3d original = object.at<cv::Vec3b>(i,j);
            if(original[0]+original[1]+original[2] == 0)
                object.at<cv::Vec3b>(i,j) = background.at<cv::Vec3b>(i,j);

        }
    }
    return object;
}

cv::Mat addBackgroundInsteadOfBlackPixelsLargeBackground(cv::Mat object, cv::Mat largeBackground) {
    // теперь вам гарантируется что largeBackground гораздо больше - добавьте проверок этого инварианта (rassert-ов)

    rassert(object.cols <= largeBackground.cols, 341241251251351);
    rassert(object.rows <= largeBackground.rows, 341241251251352);

    int iBuff = (largeBackground.rows-object.rows) / 2;
    int jBuff = (largeBackground.cols-object.cols) / 2;
    for(int i = 0; i < object.rows; i++) {
        for(int j = 0; j < object.cols; j++) {
            cv::Vec3d original = object.at<cv::Vec3b>(i,j);
            if(original[0]+original[1]+original[2] != 0)
                largeBackground.at<cv::Vec3b>(iBuff+i,jBuff+j) = original;

        }
    }

    return largeBackground;
}

cv::Mat addBackgroundInsteadOfBlackPixelsLargeBackgroundNTimes(cv::Mat object, cv::Mat largeBackground) {
    // теперь вам гарантируется что largeBackground гораздо больше - добавьте проверок этого инварианта (rassert-ов)

    rassert(object.cols <= largeBackground.cols, 341241251251353);
    rassert(object.rows <= largeBackground.rows, 341241251251354);

    int N = std::rand()%100;

    for(int n = 0; n < N; n++) {
        int iBuff = rand()%(largeBackground.rows - object.rows);
        int jBuff = rand()%(largeBackground.cols - object.cols);
        for (int i = 0; i < object.rows; i++) {
            for (int j = 0; j < object.cols; j++) {
                cv::Vec3d original = object.at<cv::Vec3b>(i, j);
                if (original[0] + original[1] + original[2] != 0)
                    largeBackground.at<cv::Vec3b>(iBuff + i, jBuff + j) = original;

            }
        }
    }

    return largeBackground;
}

cv::Mat fillBackground(cv::Mat object, cv::Mat largeBackground){
    rassert(object.cols <= largeBackground.cols, 341241251251355);
    rassert(object.rows <= largeBackground.rows, 341241251251356);

    double iK = object.rows*1.0/largeBackground.rows;
    double jK = object.cols*1.0/largeBackground.cols;
    for(int i = 0; i < largeBackground.rows; i++) {
        for(int j = 0; j < largeBackground.cols; j++) {
            cv::Vec3d original = object.at<cv::Vec3b>((int)(i*iK),(int)(j*jK));
            if(original[0]+original[1]+original[2] != 0)
                largeBackground.at<cv::Vec3b>(i,j) = original;

        }
    }

    return largeBackground;
}

cv::Mat addBackground(cv::Mat object, cv::Mat largeBackground, cv::Mat mask){
    rassert(object.cols == mask.cols, 341241251251357);
    rassert(object.rows == mask.rows, 341241251251358);
    double iK = largeBackground.rows*1.0/object.rows;
    double jK = largeBackground.cols*1.0/object.cols;
    for(int i = 0; i < object.rows; i++) {
        for(int j = 0; j < object.cols; j++) {
            cv::Vec3d original = object.at<cv::Vec3b>(i,j);
            if(mask.at<uchar>(i,j))
                object.at<cv::Vec3b>(i,j) = largeBackground.at<cv::Vec3b>((int)(iK*i), (int)(jK*j));
        }
    }
    return object;
}



cv::Mat dilate(cv::Mat mask, int r){
    cv::Mat res(mask.rows, mask.cols, CV_8UC1, cv::Scalar(0));
    for(int i = 0; i < mask.rows; i++) {
        for(int j = 0; j < mask.cols; j++) {
            bool flag = false;
            for(int i2 = std::max(0,i-r); !flag && i2 < std::min(mask.rows, i+r); i2++)
                for(int j2 = std::max(0,j-r); !flag && j2 < std::min(mask.cols, j+r); j2++)
                    flag = flag || mask.at<uchar>(i2, j2);
            res.at<uchar>(i, j) = flag;
        }
    }
    return res;
}

cv::Mat erode(cv::Mat mask, int r){
    cv::Mat res(mask.rows, mask.cols, CV_8UC1, cv::Scalar(0));
    for(int i = 0; i < mask.rows; i++) {
        for(int j = 0; j < mask.cols; j++) {
            bool flag = false;
            for(int i2 = std::max(0,i-r); !flag && i2 < std::min(mask.rows, i+r); i2++)
                for(int j2 = std::max(0,j-r); !flag && j2 < std::min(mask.cols, j+r); j2++)
                    flag = flag || !mask.at<uchar>(i2, j2);
            res.at<uchar>(i, j) = !flag;
        }
    }
    return res;
}

cv::Mat clearWithDSU(cv::Mat mask, char v, int min_size){
    DisjointSet dsu(mask.rows*mask.cols);
    for(int i = 0; i < mask.rows; i++){
        for(int j = 0; j < mask.rows; j++) {
            if(i > 0 && mask.at<char>(i,j) == v && mask.at<char>(i-1, j) == v)
                dsu.union_sets(i*mask.rows+j, (i-1)*mask.rows+j);
            if(j > 0 && mask.at<char>(i,j) == v && mask.at<char>(i, j-1) == v)
                dsu.union_sets(i*mask.rows+j, i*mask.rows+j-1);
        }
    }

    for(int i = 0; i < mask.rows; i++) {
        for (int j = 0; j < mask.rows; j++) {
            if(dsu.get_set_size(i*mask.rows+j) < min_size) {
                mask.at<char>(i, j) = !v;
            }
        }
    }
    return mask;
}


//Фон - 1, отсутствие - 0
cv::Mat getBackgroundMask(cv::Mat object, cv::Vec3b color, double dis){
    cv::Mat res(object.rows, object.cols, CV_8UC1, cv::Scalar(0));
    for(int i = 0; i < object.rows; i++) {
        for(int j = 0; j < object.cols; j++) {
            cv::Vec3d original = object.at<cv::Vec3b>(i,j);
            res.at<uchar>(i, j) = pow(original[0]-color[0], 2)+pow(original[1]-color[1], 2)+pow(original[2]-color[2], 2) <= dis*dis;
        }
    }
    return res;
}

cv::Mat getBackgroundMask(cv::Mat object, cv::Mat back, double dis){
    rassert(object.cols == back.cols, 341241251251359);
    rassert(object.rows == back.rows, 341241251251350);
    cv::Mat res(object.rows, object.cols, CV_8UC1, cv::Scalar(0));
    for(int i = 0; i < object.rows; i++) {
        for(int j = 0; j < object.cols; j++) {
            cv::Vec3d original = object.at<cv::Vec3b>(i,j);
            cv::Vec3d color = back.at<cv::Vec3b>(i,j);
            res.at<uchar>(i, j) = pow(original[0]-color[0], 2)+pow(original[1]-color[1], 2)+pow(original[2]-color[2], 2) <= dis*dis;
        }
    }
    return res;
}
