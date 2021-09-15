#include <vector>
#include <iostream>
#include <libutils/rasserts.h>

#include "helper_function.h" // подключаем функцию print2DArray(...) из соседнего файла


void task1() {
    std::vector<int> a; // динамический массив (автоматически увеличивается по мере добавления объектов)
    a.push_back(10);
    a.push_back(12);
    a.push_back(11);// добавляем в конец число 10, тем самым увеличивая этот динамический массив
    std::cout << "current size is " << a.size() << std::endl; // печатаем в консоль текущий размер

    // чтобы продолжить выполнение задания - раскомментируйте следующие строчки - проще всего это сделать выделив их все мышкой, а затем нажать Ctrl+/ (так же можно и комментировать строки)
    rassert(a.size() == 3,3412421421); // это способ проверить некоторый факт в программе, например здесь мы ожидали бы что размер вектора 1 - давайте явно это проверим, указав код ошибки на случай если это будет не так
   rassert(a.size() == 3, "vector a should of size 3!"); // можно вместо числа писать текст описывающий проблему, но на мой взгляд это слишком долго и лениво
//    // TODO 11 запустите программу, увидьте ошибку, была кинота ошибка с кодом из предыдущей строки - почему? поправьте ее
//
    a.resize(5); // изменяем размер массива, пусть он будет хранить пять чисел
   for (int i = 0; i < 5; ++i) {
       a[i] = i; // тогда мы сможем сразу в каждую из его пяти ячеек что-то положить, например числа от 0 до 4    }
   }
   std::cout << "current size is " << a.size() << std::endl;
    rassert(a.size() == 5, "vector need size 5")// печатаем в консоль текущий размер
//    // TODO 12 до запуска подумайте какой бы размер массива должен быть? добавьте сюда проверку через rassert что размер вектора тот что вы бы ожидали
}

void task2() {
    std::vector<std::vector<int>> array2d; // это динамический массив в котором каждый элемент - тоже динамический массив
    // TODO 21 добавьте rassert проверяющий размер этого двумерного вектора, как вы считаете какого размера он должен быть?
    rassert(array2d.size() == 0, "124332");
    std::vector<int> row0; // первый ряд чисел для нашего двумерного массива (row = ряд)
    row0.push_back(5);
    row0.push_back(8);
    row0.push_back(10);
    // TODO 22 добавьте rassert проверяющий размер этого вектора row0
    rassert(row0.size()== 3, "4598734907593");
    array2d.push_back(row0);
    // TODO 23 добавьте rassert проверяющий размер этого двумерного вектора array2d, как вы считаете какого размера он должен быть?
    rassert(array2d.size() == 1, "09868758768936")
    std::cout << "print2DArray(array2d):" << std::endl;
    print2DArray(array2d); // TODO 24,25: откройте соседний файл - helper_function.cpp и реализуйте там эту функцию, можете туда быстро попасть через телепорт - держите нажатым CTRL->и кликните по этой функции

    // чтобы продолжить выполнение задания - раскомментируйте следующие строчки - проще всего это сделать выделив их все мышкой, а затем нажать Ctrl+/ (так же можно и комментировать строки)
//    // теперь давайте добавим еще один ряд чисел но другим способом:
      std::vector<int> row1;
     row1.resize(3);
     row1[0] = 23;
     row1[1] = 24;
     row1[2] = 42;
     rassert(row1.size() == 3, "5987976439");
    array2d.push_back(row1);
    rassert(array2d.size() == 2, "55555345555556");
//    // TODO 26 добавьте два rassert-а - чтобы удостовериться что размеры двух динамических массивов которые мы только что изменили - совпадают с вашим ожиданием
//
    std::cout << "print2DArray(array2d):" << std::endl;
    print2DArray(array2d);
//
//    // TODO 27 добавьте еще один ряд чисел, но на этот раз из 10 чисел от 0 до 9 включительно (воспользуйтесь for-ом)
    std::vector<int> row2;
    row2.resize(10);
    for (int i = 0; i < 10; ++i) {
        row2[i] = i;
    }
    array2d.push_back(row2);
    print2DArray(array2d);
}

void task3() {
    // TODO 31 напишите следующую программу:
    std::cout << "Введите два натуральных числа от 1 до 20 включительно (число рядов и колонок)" << std::endl;
    // TODO 32 попросите пользователя ввести два натуральных числа rows, cols (число рядов и число колонок) (от 1 до 20 включительно каждое)
    int cols, rows;
    std::cin >> rows;
    std::cin >> cols;
    rassert(cols <= 20, "непонятно написано?");
    rassert(rows<=20, "читать умеешь?");
    rassert(cols >= 0, "непонятно написано?");
    rassert(rows>= 0, "читать умеешь?");
    // TODO 33 проверьте с помощью rassert что оба числа в корректном диапазоне (от 1 до 20), проверьте что если ввести плохое число - проверка срабатывает и пишет ошибку (можете использовать как число, так и сообщение)

    // TODO 34 создайте двумерный массив состоящий из rows векторов
    std::vector<std::vector<int>> array2d;
    array2d.resize(rows);
    // TODO 35 сделайте так чтобы каждый из этих rows векторов был размера cols (используйте resize)
    for (int i = 0; i < rows; ++i) {
        array2d[i].resize(cols);
    }
    // TODO 36 как думаете какие элементы сейчас лежат в двумерном массиве? проверьте выведя его в консоль
    print2DArray(array2d);
    // TODO 37 ваша программа должна считывать пары чисел i, j в вечном цикле до тех пор пока i и j не отрицательны
    while (true) {
       int i;
       int j;
       std::cin >> i;
       std::cin >> j;
       array2d[j][i] += 1;
        print2DArray(array2d);
        bool a = true;
        bool b = true;
        for (int j = 0; j < array2d.size(); ++j) { // пробегаем по каждой строке
            a = true;
            int n = array2d[j].size(); // узнаем число элементов в текущей строке
            // TODO 24 выведите все элементы этой строчки в одну строку в консоли через пробел
            for (int i = 0; i < n; ++i) {
                int value = array2d[j][i];

                if (!(value == 1)) {
                    a = false;
                }
            }
            if (!a) {
                b = a;
            }
            // взяли j-ую строку, а из нее - i-ый элемент
            // выведите в консоль это числkо
            if (b) {
                std::cout << "OX-XO-XO";
                break;
            }
            a = true;
            b = true;
        }
        a = true;
        b = true;
        for (int j = 0; j < array2d[0].size(); ++j) { // пробегаем по каждой строке
            a = true;
            int n = array2d.size(); // узнаем число элементов в текущей строке
            // TODO 24 выведите все элементы этой строчки в одну строку в консоли через пробел
            for (int i = 0; i < n; ++i) {
                int value = array2d[j][i];

                if (!(value == 1)) {
                    a = false;
                }
            }
            if (!a) {
                b = a;
            }
            // взяли j-ую строку, а из нее - i-ый элемент
            // выведите в консоль это числ
        if (b) {
            std::cout << "AX-XA-XA";
            break;
        }
        a = true;
        b = true;}

            // TODO 25 не забудьте что надо делать перевод строки после каждого выведенного ряда чисел
        }
//        // TODO 38 считав очередное i, j - увеличьте ячейку в думерном массиве находящуюся в j-ой колонке, в i-ом ряду
//        // TODO 39 выведите в консоль текущее состояние двумерного массива
//        // TODO 40 добавьте проверку что если пользователь заполнил единицами хотя бы один ряд - то выводится сообщение "OX-XO-XO" и программа завершается
//        // TODO 41 добавьте проверку что если пользователь заполнил единицами хотя бы одну колонку - то выводится сообщение "AX-XA-XA" и программа завершается
//    }

}


int main() {
    try {
      //  task1(); // TODO 13 когда выполните первое задание - закомментируйте эту строку чтобы эта функция перестала вызываться (добавьте перед нею двойной слэш - / или просто нажмите Ctrl+/)
   //    task2(); // TODO 20 раскомментируйте эту строку чтобы начать выполнять второе задание (или просто поставьте каретку в эту строку и нажмите Ctrl+/)
       task3(); // TODO 30 закомментируйте предыдущие две строки и раскоментируйте эту чтобы начать выполнять третье задание
        return 0;
    } catch (const std::exception &e) {
        std::cout << "Exception! " << e.what() << std::endl;
        return 1;
    }
}
