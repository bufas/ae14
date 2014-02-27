#pragma once

#include <set>
#include "PredSearchTree.h"

class StdSetFind : public PredSearchTree {

private:
    std::set<int> tree;
    
public:

    StdSetFind(const std::vector<int> &v) : tree(v.begin(), v.end()) {}

    virtual int pred(int x) const {
        return tree.count(x);
    }

};