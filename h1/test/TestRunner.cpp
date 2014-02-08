#include <iostream>
#include <vector>
#include "../MemoryLayout.h"
#include "../Params.h"
#include "BasicTest.h"
#include "SkipTest.h"

int main(int argc, char *argv[]) {
    std::vector<MemoryLayout> mls {
        MemoryLayout::LINEAR,
        MemoryLayout::INORDER,
        MemoryLayout::BFS
    };

    for (std::vector<MemoryLayout>::iterator it = mls.begin(); it != mls.end(); ++it) {
        std::cout << "Testing " << as_string(*it) << "..." << std::endl << std::flush;
        PredSearchTreeFactory factory(*it);

        BasicTest basic(factory);
        basic.run();

        SkipTest skip(factory);
        skip.run();
    }

    std::cout << "All OK!" << std::endl;
    return 0;
}