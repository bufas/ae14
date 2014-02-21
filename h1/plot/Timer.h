#include <sys/time.h>

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
