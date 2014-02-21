#include <sys/time.h>

// This is for perf_event_open()
#include <string.h>
#include <unistd.h>
#include <linux/perf_event.h>
#include <sys/ioctl.h>
#include <asm/unistd.h>

static long perf_event_open(struct perf_event_attr *hw_event, pid_t pid, int cpu, int group_fd, unsigned long flags);
static int init_perf_event_open(const unsigned int type, const unsigned long config);

class Timer {
public:
    Timer();
    ~Timer();

    void start();
    void stop();

    long get_microseconds() {
        long secs = after.tv_sec - before.tv_sec;
        long usecs = after.tv_usec - before.tv_usec;
        return (secs * 1000000) + usecs;
    }

    long long get_branch_misses() {
        return read_perf_event_open_value(fd_branch_misses);
    }

    long long get_cache_misses() {
        return read_perf_event_open_value(fd_cache_misses);
    }


private:
    long long read_perf_event_open_value(int fd) {
        long long count;
        int res = read(fd, &count, sizeof(long long));

        if (res > 0) return count;
        fprintf(stderr, "Error reading perf_event_open value\n");
        exit(EXIT_FAILURE);
    }

    struct timeval before;
    struct timeval after;

    // File descriptors for various counters
    int fd_branch_misses;
    int fd_cache_misses;
};

Timer::Timer() {
    fd_branch_misses = init_perf_event_open(PERF_TYPE_HARDWARE, PERF_COUNT_HW_BRANCH_MISSES);
    fd_cache_misses = init_perf_event_open(PERF_TYPE_HARDWARE, PERF_COUNT_HW_CACHE_MISSES);
}

Timer::~Timer() {
    close(fd_branch_misses);
    close(fd_cache_misses);
}

void Timer::start() {
    // Reset all counters and start them
    ioctl(fd_branch_misses, PERF_EVENT_IOC_RESET, 0); 
    ioctl(fd_branch_misses, PERF_EVENT_IOC_ENABLE, 0);
    ioctl(fd_cache_misses, PERF_EVENT_IOC_RESET, 0); 
    ioctl(fd_cache_misses, PERF_EVENT_IOC_ENABLE, 0);

    // Start timer
    gettimeofday(&before, nullptr);
}

void Timer::stop() {
    // Stop timer
    gettimeofday(&after, nullptr);

    // Stop the counters
    ioctl(fd_branch_misses, PERF_EVENT_IOC_DISABLE, 0);
    ioctl(fd_cache_misses, PERF_EVENT_IOC_DISABLE, 0);
}

/**
 * Static means that this function can only
 * be accessed from this file (in C at least).
 *
 * This method is taken directly from the man
 * page of perf_event_open(2).
 * http://man7.org/linux/man-pages/man2/perf_event_open.2.html
 */
static long perf_event_open(struct perf_event_attr *hw_event, pid_t pid, int cpu, int group_fd, unsigned long flags) {
    int ret;
    ret = syscall(__NR_perf_event_open, hw_event, pid, cpu, group_fd, flags);
    return ret;
}

/**
 * This is an adapted version of the example
 * on the man page of perf_event_open(2).
 * http://man7.org/linux/man-pages/man2/perf_event_open.2.html
 *
 * Very old, much ANSI-C, WOW, such compatible
 */
static int init_perf_event_open(const unsigned int type, const unsigned long config) {
    // Create the struct which defines what should be measured
    struct perf_event_attr pe;
    memset(&pe, 0, sizeof(struct perf_event_attr));
    pe.type   = type;
    pe.size   = sizeof(struct perf_event_attr);
    pe.config = config;

    // This should be the deafult values, no need to set
    pe.disabled       = 1;
    pe.exclude_kernel = 1;
    pe.exclude_hv     = 1;

    // Use the mysterious function to get a file descriptor for the data file
    int fd = perf_event_open(&pe, 0, -1, -1, 0);
    if (fd == -1) {
        fprintf(stderr, "Error opening leader %llx\n", pe.config);
        exit(EXIT_FAILURE);
    }

    return fd;
}

