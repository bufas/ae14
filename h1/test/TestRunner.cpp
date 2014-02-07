#include <iostream>
#include <vector>
#include "../MemoryLayout.h"
#include "../Params.h"
#include "BasicTest.h"

int main(int argc, char *argv[]) {
    std::vector<MemoryLayout> mls {
        MemoryLayout::LINEAR,
        MemoryLayout::INORDER,
        MemoryLayout::BFS
    };

    for (std::vector<MemoryLayout>::iterator it = mls.begin(); it != mls.end(); ++it) {
        cout << "Testing " << as_string(*it) << "..." << endl << flush;
        PredSearchTreeFactory factory(*it);

        BasicTest basic(factory);
        basic.run();
    }

    cout << "All OK!" << endl;
    return 0;
}