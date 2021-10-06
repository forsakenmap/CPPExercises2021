#include "helper_functions.h"

#include <libutils/rasserts.h>

cv::Mat blc(cv::Mat image) {
    int b = rand()*255/32767;
    int r = rand()*255/32767;
    int g = rand()*255/32767;
    for (unsigned char i = 0; i < image.cols; ++i) {
        for (unsigned char e = 0; e < image.rows; ++e) {
            cv::Vec3b c = image.at<cv::Vec3b>(e, i);
            if((c[0] ==(unsigned char) 0) && (c[1] == (unsigned char)0) && (c[2] == (unsigned char)0)) {

                image.at<cv::Vec3b>(e, i) = cv::Vec3b(b, r, g);
            }
        }
    }
    // ниже приведен пример как узнать цвет отдельного пикселя - состоящий из тройки чисел BGR (Blue Green Red)
    // чем больше значение одного из трех чисел - тем насыщеннее его оттенок
    // всего их диапазон значений - от 0 до 255 включительно
    // т.е. один байт, поэтому мы используем ниже тип unsigned char - целое однобайтовое неотрицательное число
    //  cv::Vec3b color = image.at<cv::Vec3b>(13, 5); // взяли и узнали что за цвет в пикселе в 14-ом ряду (т.к. индексация с нуля) и 6-ой колонке
    //  unsigned char blue = color[0]; // если это число равно 255 - в пикселе много синего, если равно 0 - в пикселе нет синего
    //  unsigned char green = color[1];
    //  unsigned char red = color[2];

    // как получить белый цвет? как получить черный цвет? как получить желтый цвет?
    // поэкспериментируйте! например можете всю картинку заполнить каким-то одним цветом

    // пример как заменить цвет по тем же координатам
    // red = 255;
    // запустите эту версию функции и посмотрите на получившуюся картинку - lesson03/resultsData/01_blue_unicorn.jpg
    // какой пиксель изменился? почему он не чисто красный?
    // image.at<cv::Vec3b>(13, 5) = cv::Vec3b(blue, green, red);

    return image;
}

cv::Mat makeAllBlackPixelsBlue(cv::Mat image) {
    // TODO реализуйте функцию которая каждый черный пиксель картинки сделает синим
    for (unsigned char i = 0; i < image.cols; ++i) {
        for (unsigned char e = 0; e < image.rows; ++e) {
            cv::Vec3b c = image.at<cv::Vec3b>(e, i);
            if((c[0] ==(unsigned char) 0) && (c[1] == (unsigned char)0) && (c[2] == (unsigned char)0)) {
                int b = 255;
                image.at<cv::Vec3b>(e, i) = cv::Vec3b(b, 0, 0);
            }
        }
    }
    // ниже приведен пример как узнать цвет отдельного пикселя - состоящий из тройки чисел BGR (Blue Green Red)
    // чем больше значение одного из трех чисел - тем насыщеннее его оттенок
    // всего их диапазон значений - от 0 до 255 включительно
    // т.е. один байт, поэтому мы используем ниже тип unsigned char - целое однобайтовое неотрицательное число
  //  cv::Vec3b color = image.at<cv::Vec3b>(13, 5); // взяли и узнали что за цвет в пикселе в 14-ом ряду (т.к. индексация с нуля) и 6-ой колонке
  //  unsigned char blue = color[0]; // если это число равно 255 - в пикселе много синего, если равно 0 - в пикселе нет синего
  //  unsigned char green = color[1];
  //  unsigned char red = color[2];

    // как получить белый цвет? как получить черный цвет? как получить желтый цвет?
    // поэкспериментируйте! например можете всю картинку заполнить каким-то одним цветом

    // пример как заменить цвет по тем же координатам
   // red = 255;
    // запустите эту версию функции и посмотрите на получившуюся картинку - lesson03/resultsData/01_blue_unicorn.jpg
    // какой пиксель изменился? почему он не чисто красный?
   // image.at<cv::Vec3b>(13, 5) = cv::Vec3b(blue, green, red);

    return image;
}

cv::Mat invertImageColors(cv::Mat image) {
    // TODO реализуйте функцию которая каждый цвет картинки инвертирует:
    // т.е. пусть ночь станет днем, а сумрак рассеется
    // иначе говоря замените каждое значение яркости x на (255-x) (т.к находится в диапазоне от 0 до 255)
    for (unsigned char i = 0; i < image.cols; ++i) {
        for (unsigned char e = 0; e < image.rows; ++e) {
            cv::Vec3b c = image.at<cv::Vec3b>(e, i);
                int r = 255 - c[2];
                int g = 255 - c[1];
                int b = 255 - c[0];
                image.at<cv::Vec3b>(e, i) = cv::Vec3b(b, g, r);
        }
    }
    return image;
}

cv::Mat addBackgroundInsteadOfBlackPixels(cv::Mat object, cv::Mat background) {
    // TODO реализуйте функцию которая все черные пиксели картинки-объекта заменяет на пиксели с картинки-фона
    // т.е. что-то вроде накладного фона получится

    // гарантируется что размеры картинок совпадают - проверьте это через rassert, вот например сверка ширины:
    rassert(object.cols == background.cols, 341241251251351);

    for (unsigned char i = 0; i < object.cols; ++i) {
        for (unsigned char e = 0; e < object.rows; ++e) {
            cv::Vec3b c = object.at<cv::Vec3b>(e, i);
            if((c[0] ==(unsigned char) 0) && (c[1] == (unsigned char)0) && (c[2] == (unsigned char)0)) {
                object.at<cv::Vec3b>(e, i) = background.at<cv::Vec3b>(e,i);
            }
        }
    }
    return object;
}

cv::Mat addBackgroundInsteadOfBlackPixelsLargeBackground(cv::Mat object, cv::Mat largeBackground) {
    rassert(object.cols < largeBackground.cols, "fgjeorigoiue");
    rassert(object.rows < largeBackground.rows, "fgjtrrtgfeorigoiue");
    int y  = (largeBackground.cols - object.cols)/2;
    int x  = (largeBackground.rows - object.rows)/2;
    for (unsigned char i = 0; i < object.cols; ++i) {
        for (unsigned char e = 0; e < object.rows; ++e) {
            cv::Vec3b c = object.at<cv::Vec3b>(e, i);
            if (!((c[0] ==(unsigned char) 0) && (c[1] == (unsigned char)0) && (c[2] == (unsigned char)0))) {
                largeBackground.at<cv::Vec3b>(e + x,i + y) = object.at<cv::Vec3b>(e, i);
            }
        }
    }
    // теперь вам гарантируется что largeBackground гораздо больше - добавьте проверок этого инварианта (rassert-ов)

    // TODO реализуйте функцию так, чтобы нарисовался объект ровно по центру на данном фоне, при этом черные пиксели объекта не должны быть нарисованы

    return largeBackground;
}

cv::Mat bg(cv::Mat object, cv::Mat largeBackground, int n) {
    rassert(object.cols < largeBackground.cols, "fgjeorigoiue");
    rassert(object.rows < largeBackground.rows, "fgjtrrtgfeorigoiue");
    for (int o = 0; o < n; ++o) {
        int y  = 0 + (rand() % static_cast<int>(largeBackground.cols - 101 - 0 + 1));
        int x  =  0 + (rand() % static_cast<int>(largeBackground.rows - 101 - 0 + 1));
        for (unsigned char i = 0; i < object.cols; ++i) {
            for (unsigned char e = 0; e < object.rows; ++e) {
                cv::Vec3b c = object.at<cv::Vec3b>(e, i);
                if (!((c[0] ==(unsigned char) 0) && (c[1] == (unsigned char)0) && (c[2] == (unsigned char)0))) {
                    largeBackground.at<cv::Vec3b>(e + x,i + y) = object.at<cv::Vec3b>(e, i);
                }
            }
        }
    }
    // теперь вам гарантируется что largeBackground гораздо больше - добавьте проверок этого инварианта (rassert-ов)

    // TODO реализуйте функцию так, чтобы нарисовался объект ровно по центру на данном фоне, при этом черные пиксели объекта не должны быть нарисованы

    return largeBackground;
}
cv::Mat tored(std::vector<int> objx, std::vector<int> objy, cv::Mat lbg) {
    for (int i = 0; i < objx.size(); ++i) {
        cv::Vec3b c = lbg.at<cv::Vec3b>(objy.at(i), objx.at(i));
        lbg.at<cv::Vec3b>(objy.at(i), objx.at(i)) = cv::Vec3b(0,0,255);
    }
    return lbg;
}
cv::Mat resize(cv::Mat img, int x, int y) {
    cv::Mat result;
    for (unsigned char i = 0; i < y; ++i) {
        for (unsigned char e = 0; e < x; ++e) {
            result.at<cv::Vec3b>(e,i) = img.at<cv::Vec3b>((int)e/img.rows, (int)i/img.cols);
        }
    }
    return result;
}
cv::Mat addbgred(cv::Mat object, cv::Mat background, std::vector<int> x, std::vector<int> y) {
    // TODO реализуйте функцию которая все черные пиксели картинки-объекта заменяет на пиксели с картинки-фона
    // т.е. что-то вроде накладного фона получится

    // гарантируется что размеры картинок совпадают - проверьте это через rassert, вот например сверка ширины:
   // rassert(object.cols == background.cols, 341241251251351);

    for (unsigned char i = 0; i < object.cols; ++i) {
        for (unsigned char e = 0; e < object.rows; ++e) {
            cv::Vec3b c = object.at<cv::Vec3b>(e, i);
            if((c[0] ==(unsigned char) 0) && (c[1] == (unsigned char)0) && (c[2] == (unsigned char)255)) {
                object.at<cv::Vec3b>(e, i) = background.at<cv::Vec3b>(e,i);
            }
        }
    }
    return object;
}
