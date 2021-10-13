#include "disjoint_set.h"

#define ROOT -1


DisjointSet::DisjointSet(int size)
{
    parents = std::vector<int>(size, ROOT);
    ranks = std::vector<int>(size, 0);
    sizes = std::vector<int>(size, 1);
}

int	DisjointSet::get_set(int element)
{
    int el = element;
    while (parents[el] != ROOT){
        el = parents[el];
    }
    while (parents[element] != ROOT){
        int element2 = parents[element];
        parents[element] = el;
        element = element2;
    }

    return el;
}

int DisjointSet::count_differents() const
{
    int count = 0;
    for (size_t i = 0; i < this->parents.size(); i++) {
        if(parents[i] == ROOT)
            count++;
    }
    return count;
}

int DisjointSet::get_set_size(int element)
{
    return sizes[get_set(element)];
}

int DisjointSet::get_set_rank(int element)
{
    return ranks[get_set(element)];
}

int	DisjointSet::union_sets(int element0, int element1)
{
    int root0 = get_set(element0),
        root1 = get_set(element1),
        size0 = sizes[root0],
        size1 = sizes[root1],
        rank0 = ranks[root0],
        rank1 = ranks[root1];

    if(root1 == root0)
        return root0;
//    if(size0 >= size1){
//        parents[root1] = root0;
//        sizes[root0] += size1;
//        return root0;
//    }else{
//        parents[root0] = root1;
//        sizes[root1] += size0;
//        return root1;
//    }

    if(rank0 == rank1){
        parents[root1] = root0;
        sizes[root0] += size1;
        ranks[root0]++;
        return root0;
    }else if(rank0 > rank1){
        parents[root1] = root0;
        sizes[root0] += size1;
        return root0;
    }else{
        parents[root0] = root1;
        sizes[root1] += size0;
        return root1;
    }
}
