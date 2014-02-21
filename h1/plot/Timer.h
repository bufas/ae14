#pragma once

#include <sys/time.h>
#include "PerfVar.h"

class Timer {
public:
    Timer(PerfVar pv) : pv(pv) {}

    // Start and stop the timer to creat a lap
    void start() {
        gettimeofday(&before, nullptr);
    }

    void stop() {
        gettimeofday(&after, nullptr);
        lap_times.push_back(calc_lap_time());
        sorted = false;
    }

    // Getters for time
    long get_avg_time(int exclude = 0) {
        sort_lap_times();
        long sum = std::accumulate(lap_times.begin() + exclude, lap_times.end() - exclude, 0l);
        return sum / (lap_times.size() - (exclude * 2));
    }

    long get_lowest_time(int exclude = 0) {
        sort_lap_times();
        return lap_times[exclude];
    }

    long get_highest_time(int exclude = 0) {
        sort_lap_times();
        return lap_times[lap_times.size() - exclude - 1];
    }

    // Getters for counters. We can only measure this on linux (look in linux/Timer.h)
    long get_avg_count(int exclude = 0) { return -1; }
    long get_lowest_count(int exclude = 0) { return -1; }
    long get_highest_count(int exclude = 0) { return -1; }

    long get_avg_ratio(int exclude = 0) { return -1; }
    long get_lowest_ratio(int exclude = 0) { return -1; }
    long get_highest_ratio(int exclude = 0) { return -1; }


private:
    void sort_lap_times() {
        if (!sorted) {
            std::sort(lap_times.begin(), lap_times.end());
            sorted = true;
        }
    }

    long calc_lap_time() {
        long secs = after.tv_sec - before.tv_sec;
        long usecs = after.tv_usec - before.tv_usec;
        return (secs * 1000000) + usecs;
    }

    struct timeval before, after;
    std::vector<long> lap_times;
    bool sorted;
    PerfVar pv;

};
