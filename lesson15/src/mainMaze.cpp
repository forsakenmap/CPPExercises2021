#include <vector>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <string>
#include <libutils/rasserts.h>

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/types.hpp>
bool found(std::vector<int> a, int b) {
    for(int i = 0; i < a.size(); i++) {
        if(a.at(i) == b) {
            return true;
        }
    }
    return false;
}

struct Edge {
    int u, v; // номера вершин которые это ребро соединяет
    int w; // длина ребра (т.е. насколько длинный путь предстоит преодолеть переходя по этому ребру между вершинами)

    Edge(int u, int v, long long w) : u(u), v(v), w(w)
    {}
};

// Эта биективная функция по координате пикселя (строчка и столбик) + размерам картинки = выдает номер вершины
int encodeVertex(int row, int column, int nrows, int ncolumns) {
    rassert(row < nrows, 348723894723980017);
    rassert(column < ncolumns, 347823974239870018);
    int vertexId = row * ncolumns + column;
    return vertexId;
}
int distance(unsigned char r1, unsigned char g1, unsigned char b1, unsigned char r2, unsigned char g2, unsigned char b2){
    return round(sqrt(pow(r2-r1,2)+pow(g2-g1,2)+pow(b2-b1,2)));
}
// Эта биективная функция по номеру вершины говорит какой пиксель этой вершине соовтетствует (эта функция должна быть симметрична предыдущей!)
cv::Point2i decodeVertex(int vertexId, int nrows, int ncolumns) {

    // TODO: придумайте как найти номер строки и столбика пикселю по номеру вершины (просто поймите предыдущую функцию и эта функция не будет казаться сложной)
    int row = vertexId/ncolumns;
    int column = vertexId-row*ncolumns;

    // сверим что функция симметрично сработала:
    rassert(encodeVertex(row, column, nrows, ncolumns) == vertexId, 34782974923035);

    rassert(row < nrows, 34723894720027);
    rassert(column < ncolumns, 3824598237592030);
    return cv::Point2i(column, row);
}

void run(int mazeNumber) {
    cv::Mat maze = cv::imread("lesson15/data/mazesImages/maze" + std::to_string(mazeNumber) + ".png");
    rassert(!maze.empty(), 324783479230019);
    rassert(maze.type() == CV_8UC3, 3447928472389020);
    std::cout << "Maze resolution: " << maze.cols << "x" << maze.rows << std::endl;

    int nvertices = maze.cols*maze.rows; // TODO

    std::vector<std::vector<Edge>> edges_by_vertex(nvertices);
    for (int i = 0; i < maze.rows; ++i) {
        for (int j = 0; j < maze.cols; ++j) {
            cv::Vec3b color = maze.at<cv::Vec3b>(i,j);
            unsigned char blue = color[0];
            unsigned char green = color[1];
            unsigned char red = color[2];

            auto ai = encodeVertex(i,j,maze.rows,maze.cols);
            if(i > 0) {
                cv::Vec3b color2 = maze.at<cv::Vec3b>(i-1,j);
                edges_by_vertex[ai].emplace_back(ai, encodeVertex(i-1,j, maze.rows, maze.cols),
                                                 distance(color2[0], color2[1], color2[2], red, green, blue)+1);
            }
            if(i < maze.rows-1) {
                cv::Vec3b color2 = maze.at<cv::Vec3b>(i+1,j);
                edges_by_vertex[ai].emplace_back(ai, encodeVertex(i+1,j, maze.rows, maze.cols),
                                                 distance(color2[0], color2[1], color2[2], red, green, blue)+1);
            }
            if(j > 0) {
                cv::Vec3b color2 = maze.at<cv::Vec3b>(i,j-1);
                edges_by_vertex[ai].emplace_back(ai, encodeVertex(i,j-1, maze.rows, maze.cols),
                                                 distance(color2[0], color2[1], color2[2], red, green, blue)+1);
            }
            if(j < maze.cols-1) {
                cv::Vec3b color2 = maze.at<cv::Vec3b>(i,j+1);
                edges_by_vertex[ai].emplace_back(ai, encodeVertex(i,j+1, maze.rows, maze.cols),
                                                 distance(color2[0], color2[1], color2[2], red, green, blue)+1);
            }
        }
    }
    int start, finish;
    if (mazeNumber >= 1 && mazeNumber <= 3) { // Первые три лабиринта очень похожи но кое чем отличаются...
        start = encodeVertex(300, 300, maze.rows, maze.cols);
        finish = encodeVertex(0, 305, maze.rows, maze.cols);
    } else if (mazeNumber == 4) {
        start = encodeVertex(154, 312, maze.rows, maze.cols);
        finish = encodeVertex(477, 312, maze.rows, maze.cols);
    } else if (mazeNumber == 5) { // Лабиринт в большом разрешении, добровольный (на случай если вы реализовали быструю Дейкстру с приоритетной очередью)
        start = encodeVertex(1200, 1200, maze.rows, maze.cols);
        finish = encodeVertex(1200, 1200, maze.rows, maze.cols);
    } else {
        rassert(false, 324289347238920081);
    }

    const int INF = std::numeric_limits<long>::max();
    cv::Mat window = maze.clone(); // на этой картинке будем визуализировать до куда сейчас дошла прокладка маршрута
    std::vector<bool> edg_be(nvertices, false);
    Edge a(0, 0, 0);
    int s = 0;
    std::vector<long long> distances(nvertices, INF);
    distances.at(0) = 0;
    int min = INF;
    int num = 0;
    std::vector<std::string> put(nvertices, "");
    std::vector<int> first_s;
    first_s.push_back(start);
    std::vector<int> second_s;
    // TODO ...
    while (true) {
        for (int i = 0; i < first_s.size(); i++) {
            for (int k = 0; k < edges_by_vertex[first_s.at(i)].size(); k++) {
                a = edges_by_vertex[first_s.at(i)].at(k);
             //   if ((!edg_be.at(first_s.at(i))) && (!found(second_s, a.v))) {
            //        second_s.push_back(a.v);
             //   }
                if (distances.at(a.v) > distances.at(a.u) + a.w) {
                    if(!found(second_s, a.v)) {
                        second_s.push_back(a.v);
                    }
                   // cv::imshow("Maze", window);
                   // cv::waitKey(1);
                   cv::Point2i p = decodeVertex(a.u, maze.rows, maze.cols);
                   window.at<cv::Vec3b>(p.y, p.x) = cv::Vec3b(0, 0, 255);
                    distances.at(a.v) = distances.at(a.u) + a.w;
                    put.at(a.v) = put.at(a.u) + " " + std::to_string(a.v + 1);
                   // cv::Point2i p = decodeVertex(a.u, maze.rows, maze.cols);
                   // window.at<cv::Vec3b>(p.y, p.x) = cv::Vec3b(0, 255, 0);
                }
            }
            edg_be.at(first_s.at(i)) = true;
        }
        if (second_s.empty()) {
            break;
        }
        first_s = second_s;
        second_s = std::vector<int>();
    }
    std::string sd = std::to_string(start) + put.at(finish);;
    std::vector<int> N;
    int n;
    std::istringstream ss(sd);

    while(ss >> n) N.push_back(n);

    for(auto i : N) {
        cv::Point2i p = decodeVertex(i+1, maze.rows, maze.cols);
      window.at<cv::Vec3b>(p.y, p.x) = cv::Vec3b(0, 255, 0);
    }
    std::cout << std::to_string(start) + put.at(finish);
        cv::imshow("Maze", window);
        cv::waitKey(1);

    // TODO СКОПИРУЙТЕ СЮДА ДЕЙКСТРУ ИЗ ПРЕДЫДУЩЕГО ИСХОДНИКА

    // TODO в момент когда вершина становится обработанной - красьте ее на картинке window в зеленый цвет и показывайте картинку:
    //    cv::Point2i p = decodeVertex(the_chosen_one, maze.rows, maze.cols);
    //    window.at<cv::Vec3b>(p.y, p.x) = cv::Vec3b(0, 255, 0);
   // cv::Point2i p = decodeVertex(a, maze.rows, maze.cols);
   // window.at<cv::Vec3b>(p.y, p.x) = cv::Vec3b(0, 0, 255);
    //    cv::imshow("Maze", window);
    //    cv::waitKey(1);
    // TODO это может тормозить, в таком случае показывайте window только после обработки каждой сотой вершины

    // TODO обозначьте найденный маршрут красными пикселями

    // TODO сохраните картинку window на диск
    std::cout << "" << std::endl;
    std::cout << "Finished!" << std::endl;
    std::cout << distances.at(finish);
    // Показываем результат пока пользователь не насладиться до конца и не нажмет Escape
    while (cv::waitKey(10) != 27) {
        cv::imshow("Maze", window);
    }
}

int main() {
    try {
        int mazeNumber = 1;
        run(mazeNumber);

        return 0;
    } catch (const std::exception &e) {
        std::cout << "Exception! " << e.what() << std::endl;
        return 1;
    }
}