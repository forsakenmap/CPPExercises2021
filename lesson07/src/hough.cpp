#include "hough.h"

#include <libutils/rasserts.h>
#include <iostream>

cv::Mat buildHough(cv::Mat sobel) {// единственный аргумент - это результат свертки Собелем изначальной картинки
    // проверяем что входная картинка - одноканальная и вещественная:
    rassert(sobel.type() == CV_32FC1, 237128273918006);

    int width = sobel.cols;
    int height = sobel.rows;

    // решаем какое максимальное значение у параметра theta в нашем пространстве прямых
    int max_theta = 360;

    // решаем какое максимальное значение у параметра r в нашем пространстве прямых:
    int max_r = sqrt(sobel.cols*sobel.cols+sobel.rows*sobel.rows); // TODO замените это число так как вам кажется правильным (отталкиваясь от разрешения картинки - ее ширины и высоты)


    // создаем картинку-аккумулятор, в которой мы будем накапливать суммарные голоса за прямые
    // так же известна как пространство Хафа
    cv::Mat accumulator( sqrt(sobel.cols*sobel.cols+sobel.rows*sobel.rows), 360, CV_32FC1); // TODO подумайте какого разрешения она должна быть и поправьте ее размер

    // TODO не забудьте заполнить эту матрицу-картинку-аккумулятор нулями (очистить)
    for (int j = 0; j < accumulator.rows; ++j) {
        for (int i = 0; i < accumulator.cols; ++i) {
            accumulator.at<float>(j, i) = 0;
        }
    }
    // проходим по всем пикселям нашей картинки (уже свернутой оператором Собеля)
    for (int y0 = 0; y0 < height; ++y0) {
        for (int x0 = 0; x0 < width; ++x0) {
            // смотрим на пиксель с координатами (x0, y0)
        //    std::cout << "sobel" << std::endl;
            float strength = sobel.at<float>(y0, x0);// TODO считайте его "силу градиента" из картинки sobel

            // теперь для текущего пикселя надо найти все возможные прямые которые через него проходят
            // переберем параметр theta по всему возможному диапазону (в градусах):
            for (int theta0 = 0; theta0 < max_theta; ++theta0) {
                // TODO рассчитайте на базе информации о том какие координаты у пикселя - (x0, y0) и какой параметр theta0 мы сейчас рассматриваем
                // TODO обратите внимание что функции sin/cos принимают углы в радианах, поэтому сначала нужно пересчитать theta0 в радианы (воспользуйтесь константой PI)
                const double PI = 3.14159265358979323846264338327950288;
                double rad = theta0 * PI / 180.0;
                float r0 = x0 * cos(rad) + y0 * sin(rad);

                // TODO теперь рассчитайте координаты пикслея в пространстве Хафа (в картинке-аккумуляторе) соответсвующего параметрам theta0, r0

//                for (int j = 0; j < accumulator.rows; ++j) {
//                    for (int i = 0; i < accumulator.cols; ++i) {

                // чтобы проверить не вышли ли мы за пределы картинки-аккумулятора - давайте явно это проверим:
//                rassert(i >= 0, 237891731289044);
//                rassert(i < accumulator.cols, 237891731289045);
//                rassert(j >= 0, 237891731289046);
//                rassert(j < accumulator.rows, 237891731289047);
                // теперь легко отладить случай выхода за пределы картинки
                // TODO просто поставьте точку остановки внутри rassert:
                // нажмите Ctrl+Shift+N -> rasserts.cpp
                // и поставьте точку остановки на 8 строке: "return line;"
                if((int)r0 < 0 || (int)r0 >= max_r)
                    continue;

           //     std::cout << "accum " << r0 << " " << theta0 << std::endl;
                accumulator.at<float>((int)r0, theta0) += strength;
//                    }
                // TODO и добавьте в картинку-аккумулятор наш голос с весом strength (взятый из картинки свернутой Собелем)

//                    }
                }
            }

    }
   // std::cout << "fin" << std::endl;

    return accumulator;
}
