#include <iostream>
#include <libutils/rasserts.h>
#include "blur.h" // TODO реализуйте функцию блюра с произвольной силой размытия в файле blur.cpp

void testSomeBlur() {
    cv::Mat img = cv::imread("C:\\Users\\fabrichnikovms.23\\Downloads\\081.jpg");
    cv::Mat res = blur(img, 1, 3);
    cv::imwrite("lesson06/resultsData/08.jpg", res);
    // TODO выберите любую картинку и любую силу сглаживания - проверьте что результат - чуть размытая картинка
    // Входные картинки для тестирования возьмите из предыдущего урока (т.е. по пути lesson05/data/*).
    // Результирующие картинки сохарняйте в эту папку (т.е. по пути lesson06/resultsData/*).
}

void testManySigmas() {
    // TODO возьмите ту же самую картинку но теперь в цикле проведите сглаживание для нескольких разных сигм
    // при этом результирующую картинку сохраняйте с указанием какая сигма использовалась:
    // для того чтобы в название файла добавить значение этой переменной -
    // воспользуйтесь функцией преобразующей числа в строчки - std::to_string(sigma)
    cv::Mat img = cv::imread("C:\\Users\\fabrichnikovms.23\\Downloads\\081.jpg");
    for(int i = 1; i < 20; i++) {
        cv::Mat res = blur(img, i, 3);
        cv::imwrite("lesson06/resultsData/08_08_" + std::to_string(i) + ".jpg", res);
    }
}

int main() {
    try {
        testSomeBlur();
        testManySigmas();

        return 0;
    } catch (const std::exception &e) {
        std::cout << "Exception! " << e.what() << std::endl;
        return 1;
    }
}

