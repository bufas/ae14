#include <iostream>
#include <vector>

class PredSearchTree {

public:

    PredSearchTree(std::vector<int> v) explicit {}
    virtual ~PredSearchTree() {}

    virtual int pred(int x) = 0;

};