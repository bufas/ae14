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
