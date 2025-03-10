#pragma once

#include <vector>

class DisjointSet {
public:
    DisjointSet(int size); // конструктор - создает size элементов, каждый элемент - состоит в своем личном множестве (размера 1)

    int get_set(int element); // говорит номер множества в котором состоит данный элемент
    int get_set_size(int element); // говорит размер множества в котором состоит данный элемент
    int union_sets(int element0, int element1); // объединяет два множества в одно (два аргумента задают множества - это какие-то элементы этих двух множеств)
    int count_differents() const; // говорит сколько сейчас есть разных множеств
    int get_set_rank(int element);

protected:
    std::vector<int> parents; // массив который для каждого элемента хранит номер его родителя в подвешенном дереве (или ROOT=-1 если вершина - корень множества и родителя нет)
    std::vector<int> ranks;   // оценка того насколько дерево высокое (насколько плохо сбалансировано) в множестве у этой вершины, если она является корнем
    std::vector<int> sizes;   // точный размер множества в котором лежит эта вершина, если эта вершина является корнем
};
