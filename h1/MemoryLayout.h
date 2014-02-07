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
    VEB
};

/**
 * Simple mapping from MemoryLayout values to strings
 */
std::string as_string(const MemoryLayout &ml) {
    switch (ml) {
        case MemoryLayout::LINEAR:  return "Linear";
        case MemoryLayout::INORDER: return "Inorder";
        case MemoryLayout::BFS:     return "BFS";
        case MemoryLayout::DFS:     return "DFS";
        case MemoryLayout::VEB:     return "vEB";
        default:      return nullptr;
    }
}