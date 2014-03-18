#pragma once

#include <string>

enum class PerfVar {
    BRANCH,             // Branch instructions + branch mispredictions
    BPU,                // BPU (branch prediction unit) accesses/misses
    HW_CACHE,           // Usually same as LL_CACHE but can vary
    LL_CACHE,           // LL cache accesses/misses
    L1_CACHE,           // L1 cache accesses/misses
    DATA_TLB            // Data TLB accesses/misses
};

std::string as_string(const PerfVar &pv) {
    switch (pv) {
        case PerfVar::BRANCH:   return "Branch";
        case PerfVar::BPU:      return "Branch Prediction Unit (BPU)";
        case PerfVar::HW_CACHE: return "Hardware cache (usually Last-Level Cache)";
        case PerfVar::LL_CACHE: return "Last-Level Cache";
        case PerfVar::L1_CACHE: return "Level 1 Data Cache";
        case PerfVar::DATA_TLB: return "Data TLB";

        default:                return nullptr;
    }
}