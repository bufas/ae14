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
        MemoryLayout::BFS,
        MemoryLayout::DFS,
        // MemoryLayout::INORDER_EXPLICIT,
        // MemoryLayout::INORDER_EXPLICIT_INT,
        // MemoryLayout::BFS_EXPLICIT,
        MemoryLayout::BFS_EXPLICIT_INT,
        MemoryLayout::DFS_EXPLICIT,
        MemoryLayout::DFS_EXPLICIT_INT,
        // MemoryLayout::VEB_EXPLICIT,
        // MemoryLayout::VEB_EXPLICIT_INT
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