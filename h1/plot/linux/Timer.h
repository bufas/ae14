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

static long perf_event_open(struct perf_event_attr *hw_event, pid_t pid, int cpu, int group_fd, unsigned long flags);

class Timer {
public:
    Timer();
    ~Timer();

    void start();
    void stop();

    long get_microseconds() {
        long secs  = after.tv_sec  - before.tv_sec;
        long usecs = after.tv_usec - before.tv_usec;
        return (secs * 1000000) + usecs;
    }

    long long get_branch_misses() {
        return read_perf_event_open_value("branch", PERF_COUNT_HW_BRANCH_MISSES);
    }

    long long get_cache_misses() {
        return read_perf_event_open_value("branch", PERF_COUNT_HW_CACHE_MISSES);
    }


private:
    long long read_perf_event_open_value(const std::string &group, const unsigned long config);

    void init_perf_event_open(const std::string &group, const unsigned int type, const unsigned long config);

    struct timeval before;
    struct timeval after;

    // File descriptors for various counters
    std::vector<int> open_handles;

    std::unordered_map<std::string, int> leaders;
    std::unordered_map<std::string, std::vector<unsigned long>> configs;
};

Timer::Timer() {
    // init_perf_event_open("branch", PERF_TYPE_HARDWARE, PERF_COUNT_HW_BRANCH_INSTRUCTIONS);
    init_perf_event_open("branch", PERF_TYPE_HARDWARE, PERF_COUNT_HW_BRANCH_MISSES);

    // init_perf_event_open("cache", PERF_TYPE_HARDWARE, PERF_COUNT_HW_CACHE_REFERENCES);
    init_perf_event_open("branch", PERF_TYPE_HARDWARE, PERF_COUNT_HW_CACHE_MISSES);
}

Timer::~Timer() {
    for (auto i = open_handles.begin(); i != open_handles.end(); ++i) close(*i);
}

void Timer::start() {
    // Reset all counters and start them
    for (auto i = leaders.begin(); i != leaders.end(); ++i) {
        ioctl(i->second, PERF_EVENT_IOC_RESET, 0); 
        ioctl(i->second, PERF_EVENT_IOC_ENABLE, 0);
    }

    // Start timer
    gettimeofday(&before, nullptr);
}

void Timer::stop() {
    // Stop timer
    gettimeofday(&after, nullptr);

    // Stop the counters
    for (auto i = leaders.begin(); i != leaders.end(); ++i) {
        ioctl(i->second, PERF_EVENT_IOC_DISABLE, 0);
    }
}

long long Timer::read_perf_event_open_value(const std::string &group, const unsigned long config) {
    // Check if the group exists
    if (leaders.count(group) == 0) {
        std::cout << "Error! Reading a value from a non existant group ("<<group<<")\n" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Get the leader of the group (file descriptor)
    int leader = leaders.find(group)->second;

    // Read from the leader
    long long results[configs[group].size() + 1];
    int ret = read(leader, &results, sizeof(results));

    // std::cout << "Printing results [";
    // for (int i = 0; i < configs[group].size() + 1; i++) std::cout << " " << results[i];
    // std::cout << " ]" << std::endl;

    // Check for errors while reading
    if (ret < 0) {
        fprintf(stderr, "Error reading perf_event_open values\n");
        exit(EXIT_FAILURE);
    }

    // Return the requested value
    auto v = configs[group];
    for (int i = 0; i < v.size(); ++i) {
        if (v[i] == config) {
            return results[i + 1];
        }
    }
}


/**
 * This is an adapted version of the example
 * on the man page of perf_event_open(2).
 * http://man7.org/linux/man-pages/man2/perf_event_open.2.html
 *
 * Very old, much ANSI-C, WOW, such compatible
 */
void Timer::init_perf_event_open(const std::string &group, const unsigned int type, const unsigned long config) {
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
    auto it_group_leader = leaders.find(group);
    if (it_group_leader == leaders.end()) {
        // Create a leader
        pe.disabled    = 1;
        pe.read_format = PERF_FORMAT_GROUP;

        new_fd = perf_event_open(&pe, 0, -1, -1, 0);
        if (new_fd == -1) {
            fprintf(stderr, "Error opening leader %llx\n", pe.config);
            exit(EXIT_FAILURE);
        }

        // Update the hardware leader
        leaders[group] = new_fd;
    }
    else {
        // Create a slave
        pe.disabled = 0; // Slaves are still disabled when leader is disabled
        new_fd = perf_event_open(&pe, 0, -1, it_group_leader->second, 0);
        if (new_fd == -1) {
            fprintf(stderr, "Error connecting to leader %llx. Errno: %d\n", pe.config, errno);
            exit(EXIT_FAILURE);
        }
    }

    open_handles.push_back(new_fd);   // Remember the file descriptors so we can close them again
    configs[group].push_back(config); // Remember the index of the configs so they can be read
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
