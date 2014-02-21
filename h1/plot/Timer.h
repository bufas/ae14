#include <sys/time.h>

/*
 * TODO
 *   - The timer should remember all measured results between every
 *     start and stop.
 *   - Timer should do one of the following hardware measurements
 *       - Branch instructions + branch mispredictions
 *       - BPU (branch prediction unit) accesses/misses
 *       - LL cache accesses/misses
 *       - L1 cache accesses/misses
 *       - Data TLB accesses/misses
 *   - Timer should be able to answer the following queries
 *       - Average time of each interval excluding n highest and lowest values
 *       - n'th lowest time
 *       - n'th highest time
 *       - Average counter value of each interval excluding n highest and lowest
 *       - n'th lowest counter value
 *       - n'th highest counter value
 *       - Average ratio (accesses/misses) excluding n highest and lowest
 *       - n'th lowest ratio
 *       - n'th highest ratio
 */

class Timer {
public:
    void start();
    void stop();

    long get_microseconds() {
        long secs = after.tv_sec - before.tv_sec;
        long usecs = after.tv_usec - before.tv_usec;
        return (secs * 1000000) + usecs;
    }

    // We can only measure this on linux (look in linux/Timer.h)
    long long get_branch_misses() { return 0; }
    long long get_cache_misses() { return 0; }

private:
    struct timeval before;
    struct timeval after;

};

void Timer::start() {
    gettimeofday(&before, nullptr);
}

void Timer::stop() {
    gettimeofday(&after, nullptr);
}
