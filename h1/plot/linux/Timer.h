#include <sys/time.h>

// This is for perf_event_open()
#include <string.h>
#include <unistd.h>
#include <linux/perf_event.h>
#include <sys/ioctl.h>
#include <asm/unistd.h>

static long perf_event_open(struct perf_event_attr *hw_event, pid_t pid, int cpu, int group_fd, unsigned long flags);

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
        return read_perf_event_open_value(fd_hw, PERF_COUNT_HW_BRANCH_MISSES);
    }

    long long get_cache_misses() {
        return read_perf_event_open_value(fd_hw, PERF_COUNT_HW_CACHE_MISSES);
    }


private:
    long long read_perf_event_open_value(const int &fd, const unsigned long config);

    void init_perf_event_open(long &fd, const unsigned int type, const unsigned long config);

    struct timeval before;
    struct timeval after;

    // File descriptors for various counters
    long fd_hw;
    std::vector<unsigned long> configs;
    std::vector<long> open_handles;
};

Timer::Timer() : fd_hw(-1) {
    init_perf_event_open(fd_hw, PERF_TYPE_HARDWARE, PERF_COUNT_HW_BRANCH_MISSES);
    init_perf_event_open(fd_hw, PERF_TYPE_HARDWARE, PERF_COUNT_HW_CACHE_MISSES);
}

Timer::~Timer() {
    for (auto i = open_handles.begin(); i < open_handles.end(); ++i) close(*i);
}

void Timer::start() {
    // Reset all counters and start them
    ioctl(fd_hw, PERF_EVENT_IOC_RESET, 0); 
    ioctl(fd_hw, PERF_EVENT_IOC_ENABLE, 0);

    // Start timer
    gettimeofday(&before, nullptr);
}

void Timer::stop() {
    // Stop timer
    gettimeofday(&after, nullptr);

    // Stop the counters
    ioctl(fd_hw, PERF_EVENT_IOC_DISABLE, 0);
}

long long Timer::read_perf_event_open_value(const int &fd, const unsigned long config) {
    // Read from the file descriptor
    long long results[1 + configs.size()];
    int res = read(fd, &results, sizeof(results));

    std::cout << "Printing results [";
    for (int i = 0; i < 1 + configs.size(); i++) std::cout << " " << results[i];
    std::cout << " ]" << std::endl;

    // Check for errors while reading
    if (res < 0) {
        fprintf(stderr, "Error reading perf_event_open value\n");
        exit(EXIT_FAILURE);
    }

    // Return the requested value
    for (int i = 0; i < configs.size(); ++i) {
        if (configs[i] == config) {
            return results[i+1];
        }
    }

    std::cout << "ERROR! The requested value was not found." << std::endl;
    return -1000000000;
}


/**
 * This is an adapted version of the example
 * on the man page of perf_event_open(2).
 * http://man7.org/linux/man-pages/man2/perf_event_open.2.html
 *
 * Very old, much ANSI-C, WOW, such compatible
 */
void Timer::init_perf_event_open(long &fd, const unsigned int type, const unsigned long config) {
    // Create the struct which defines what should be measured
    struct perf_event_attr pe;
    memset(&pe, 0, sizeof(struct perf_event_attr));
    pe.size   = sizeof(struct perf_event_attr);
    pe.type   = type;
    pe.config = config;

    // This should be the deafult values, no need to set
    pe.exclude_kernel = 1;
    pe.exclude_hv     = 1;

    // Use the mysterious function to get a file descriptor for the data file
    if (fd == -1) {
        pe.disabled    = 1;
        pe.read_format = PERF_FORMAT_GROUP;
        fd = perf_event_open(&pe, 0, -1, -1, 0);
        if (fd == -1) {
            fprintf(stderr, "Error opening leader %llx\n", pe.config);
            exit(EXIT_FAILURE);
        }
        std::cout << "fd == " << fd << std::endl;
        open_handles.push_back(fd);
    }
    else {
        pe.disabled    = 0;
        int ret = perf_event_open(&pe, 0, -1, fd, 0);
        if (ret == -1) {
            fprintf(stderr, "Error connecting to leader %llx\n", pe.config);
            exit(EXIT_FAILURE);
        }
        std::cout << "ret == " << ret << std::endl;
        open_handles.push_back(ret);
    }

    configs.push_back(config); // TODO this only accomodates type = HARDWARE
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
    return syscall(__NR_perf_event_open, hw_event, pid, cpu, group_fd, flags);
}
