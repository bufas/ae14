#pragma once

#include <iostream>
#include <vector>

class PredSearchTree {

public:

    virtual ~PredSearchTree() {}

    virtual int pred(int x) = 0;

};