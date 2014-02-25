#pragma once

#include <string>

/**
 * The different supported memory layouts.
 */
enum class MemoryLayout {
    LINEAR,
    
    INORDER,
    BFS,
    DFS,
    VEB,

    INORDER_EXPLICIT,
    BFS_EXPLICIT,
    DFS_EXPLICIT,
    VEB_EXPLICIT,

    INORDER_EXPLICIT_INT,
    BFS_EXPLICIT_INT,
    DFS_EXPLICIT_INT,
    VEB_EXPLICIT_INT,

    CONSTANT
};

/**
 * Simple mapping from MemoryLayout values to strings
 */
std::string as_string(const MemoryLayout &ml) {
    switch (ml) {
        case MemoryLayout::LINEAR:               return "Linear";

        case MemoryLayout::INORDER:              return "Inorder";
        case MemoryLayout::BFS:                  return "BFS";
        case MemoryLayout::DFS:                  return "DFS";
        case MemoryLayout::VEB:                  return "vEB";

        case MemoryLayout::INORDER_EXPLICIT:     return "explicit inorder";
        case MemoryLayout::BFS_EXPLICIT:         return "explicit BFS";
        case MemoryLayout::DFS_EXPLICIT:         return "explicit DFS";
        case MemoryLayout::VEB_EXPLICIT:         return "explicit vEB";

        case MemoryLayout::INORDER_EXPLICIT_INT: return "explicit int inorder";
        case MemoryLayout::BFS_EXPLICIT_INT:     return "explicit int BFS";
        case MemoryLayout::DFS_EXPLICIT_INT:     return "explicit int DFS";
        case MemoryLayout::VEB_EXPLICIT_INT:     return "explicit int vEB";

        case MemoryLayout::CONSTANT:             return "constant";

        default:                                 return nullptr;
    }
}