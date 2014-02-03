#include <iostream>
#include "LinearSearchTest.h"
#include "InorderBinSearchTest.h"
#include "BFSBinSearchTest.h"

int main(int argc, char *argv[]) {
    LinearSearchTest lst;
    lst.run();

    InorderBinSearchTest ibst;
    ibst.run();

    BFSBinSearchTest bfsbst;
    bfsbst.run();

    cout << "All OK!" << endl;
    return 0;
}