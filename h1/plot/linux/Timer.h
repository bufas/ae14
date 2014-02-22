#include <sys/time.h>
#include <vector>
#include <string>
#include <unordered_map>
#include <cerrno>

// This is for perf_event_open()
#include <string.h>
#include <unistd.h>
#include <linux/perf_event.h>
#include <sys/ioctl.h>
#include <asm/unistd.h>

#include "../PerfVar.h"

static long perf_event_open(struct perf_event_attr *hw_event, pid_t pid, int cpu, int group_fd, unsigned long flags);

class Timer {
public:
    Timer(const PerfVar &pv);
    ~Timer();

    void start();
    void stop();

    // Getters for time
    long get_avg_time(int exclude = 0)     { sort_times(); return get_avg(times, exclude); }
    long get_lowest_time(int exclude = 0)  { sort_times(); return times[exclude]; }
    long get_highest_time(int exclude = 0) { sort_times(); return times[times.size() - exclude - 1]; }

    // Getters for counters
    long get_avg_count_miss(int exclude = 0)     { sort_misses(); return get_avg(misses, exclude); }
    long get_lowest_count_miss(int exclude = 0)  { sort_misses(); return misses[exclude]; }
    long get_highest_count_miss(int exclude = 0) { sort_misses(); return misses[misses.size() - exclude - 1]; }

    long get_avg_count_access(int exclude = 0)     { sort_accesses(); return get_avg(accesses, exclude); }
    long get_lowest_count_access(int exclude = 0)  { sort_accesses(); return accesses[exclude]; }
    long get_highest_count_access(int exclude = 0) { sort_accesses(); return accesses[accesses.size() - exclude - 1]; }

    double get_avg_count_ratio(int exclude = 0)     { sort_ratios(); return get_avg(ratios, exclude); }
    double get_lowest_count_ratio(int exclude = 0)  { sort_ratios(); return ratios[exclude]; }
    double get_highest_count_ratio(int exclude = 0) { sort_ratios(); return ratios[ratios.size() - exclude - 1]; }

private:
    // Precondition: the vector must be sorted
    // Template as it must support both long and double
    template<typename T>
    T get_avg(const std::vector<T> &v, int exclude) {
        T sum = std::accumulate(v.begin() + exclude, v.end() - exclude, 0l);
        return sum / (v.size() - (exclude * 2));
    }

    void sort_times()    { sort_counter(times,    times_sorted);    }
    void sort_misses()   { sort_counter(misses,   misses_sorted);   }
    void sort_accesses() { sort_counter(accesses, accesses_sorted); }
    void sort_ratios()   { sort_counter(ratios,   ratios_sorted);   }

    // Template as it must support both long and double
    template<typename T>
    void sort_counter(std::vector<T> &v, bool &b) {
        if (!b) std::sort(v.begin(), v.end());
        b = true;
    }

    long calc_lap_time() {
        long secs = after.tv_sec - before.tv_sec;
        long usecs = after.tv_usec - before.tv_usec;
        return (secs * 1000000) + usecs;
    }

    unsigned long calc_cache_config(unsigned int cache, unsigned int op, unsigned int result) {
        return (cache) | (op << 8) | (result << 16);
    }

    long long read_perf_event_open_value(int ct);
    void init_perf_event_open(const unsigned int type, const unsigned long config);

    PerfVar pv;
    struct timeval before;
    struct timeval after;
    std::vector<long> times;
    std::vector<long> misses;
    std::vector<long> accesses;
    std::vector<double> ratios;
    bool times_sorted;
    bool misses_sorted;
    bool accesses_sorted;
    bool ratios_sorted;

    // File descriptors for various counters
    std::vector<int> handles; // Leader is handle[0]
};

Timer::Timer(const PerfVar &pv) : pv(pv) {
    switch(pv) {
        case PerfVar::BRANCH:
            init_perf_event_open(PERF_TYPE_HARDWARE, PERF_COUNT_HW_BRANCH_MISSES);
            init_perf_event_open(PERF_TYPE_HARDWARE, PERF_COUNT_HW_BRANCH_INSTRUCTIONS);
            break;
        case PerfVar::BPU:
            init_perf_event_open(PERF_TYPE_HW_CACHE, calc_cache_config(PERF_COUNT_HW_CACHE_BPU, PERF_COUNT_HW_CACHE_OP_READ, PERF_COUNT_HW_CACHE_RESULT_MISS));
            init_perf_event_open(PERF_TYPE_HW_CACHE, calc_cache_config(PERF_COUNT_HW_CACHE_BPU, PERF_COUNT_HW_CACHE_OP_READ, PERF_COUNT_HW_CACHE_RESULT_ACCESS));
            break;
        case PerfVar::HW_CACHE:
            init_perf_event_open(PERF_TYPE_HARDWARE, PERF_COUNT_HW_CACHE_MISSES);
            init_perf_event_open(PERF_TYPE_HARDWARE, PERF_COUNT_HW_CACHE_REFERENCES);
            break;
        case PerfVar::LL_CACHE:
            init_perf_event_open(PERF_TYPE_HW_CACHE, calc_cache_config(PERF_COUNT_HW_CACHE_LL, PERF_COUNT_HW_CACHE_OP_READ, PERF_COUNT_HW_CACHE_RESULT_MISS));
            init_perf_event_open(PERF_TYPE_HW_CACHE, calc_cache_config(PERF_COUNT_HW_CACHE_LL, PERF_COUNT_HW_CACHE_OP_READ, PERF_COUNT_HW_CACHE_RESULT_ACCESS));
            break;
        case PerfVar::L1_CACHE:
            init_perf_event_open(PERF_TYPE_HW_CACHE, calc_cache_config(PERF_COUNT_HW_CACHE_L1D, PERF_COUNT_HW_CACHE_OP_READ, PERF_COUNT_HW_CACHE_RESULT_MISS));
            init_perf_event_open(PERF_TYPE_HW_CACHE, calc_cache_config(PERF_COUNT_HW_CACHE_L1D, PERF_COUNT_HW_CACHE_OP_READ, PERF_COUNT_HW_CACHE_RESULT_ACCESS));
            break;
        case PerfVar::DATA_TLB:
            init_perf_event_open(PERF_TYPE_HW_CACHE, calc_cache_config(PERF_COUNT_HW_CACHE_DTLB, PERF_COUNT_HW_CACHE_OP_READ, PERF_COUNT_HW_CACHE_RESULT_MISS));
            init_perf_event_open(PERF_TYPE_HW_CACHE, calc_cache_config(PERF_COUNT_HW_CACHE_DTLB, PERF_COUNT_HW_CACHE_OP_READ, PERF_COUNT_HW_CACHE_RESULT_ACCESS));
            break;
    }
}

Timer::~Timer() {
    // Close all open file handles
    for (auto i = handles.begin(); i != handles.end(); ++i) close(*i);
}

void Timer::start() {
    // Reset all counters and start them
    ioctl(handles[0], PERF_EVENT_IOC_RESET, 0); 
    ioctl(handles[0], PERF_EVENT_IOC_ENABLE, 0);

    // Start timer
    gettimeofday(&before, nullptr);
}

void Timer::stop() {
    // Stop timer
    gettimeofday(&after, nullptr);

    // Stop the counters
    ioctl(handles[0], PERF_EVENT_IOC_DISABLE, 0);

    // Update value lists
    times.push_back(calc_lap_time());
    misses.push_back(read_perf_event_open_value(0));
    accesses.push_back(read_perf_event_open_value(1));
    ratios.push_back((100.0 * read_perf_event_open_value(0)) / read_perf_event_open_value(1));
    times_sorted = misses_sorted = accesses_sorted = ratios_sorted = false;
}

/**
 * The parameter should be either 0 or 1.
 *   - 0 will return counter misses
 *   - 1 will return counter accesses
 */
long long Timer::read_perf_event_open_value(int ct) {
    // Read from the leader
    long long results[3]; // nr + 2 values
    int ret = read(handles[0], &results, sizeof(results));

    // Check for errors while reading
    if (ret < 0) {
        fprintf(stderr, "Error reading perf_event_open values\n");
        exit(EXIT_FAILURE);
    }

    // Return the requested value
    return results[ct + 1];
}

/**
 * This is an adapted version of the example
 * on the man page of perf_event_open(2).
 * http://man7.org/linux/man-pages/man2/perf_event_open.2.html
 *
 * Very old, much ANSI-C, WOW, such compatible
 */
void Timer::init_perf_event_open(const unsigned int type, const unsigned long config) {
    // Create the struct which defines what should be measured
    struct perf_event_attr pe;
    memset(&pe, 0, sizeof(struct perf_event_attr));
    pe.size           = sizeof(struct perf_event_attr);
    pe.type           = type;
    pe.config         = config;
    pe.exclude_kernel = 1;
    pe.exclude_hv     = 1;

    // Use the mysterious function to get a file descriptor for the data file
    int new_fd;
    if (handles.size() == 0) {
        // Create a leader
        pe.disabled    = 1;
        pe.read_format = PERF_FORMAT_GROUP;

        new_fd = perf_event_open(&pe, 0, -1, -1, 0);
        if (new_fd == -1) {
            fprintf(stderr, "Error opening leader %llx\n", pe.config);
            exit(EXIT_FAILURE);
        }
    }
    else {
        // Create a slave
        pe.disabled = 0; // Slaves are still disabled when leader is disabled
        new_fd = perf_event_open(&pe, 0, -1, handles[0], 0);
        if (new_fd == -1) {
            fprintf(stderr, "Error connecting to leader %llx. Errno: %d\n", pe.config, errno);
            exit(EXIT_FAILURE);
        }
    }

    handles.push_back(new_fd); // Remember the file descriptors so we can close them again
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
