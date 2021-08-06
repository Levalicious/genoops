#include "time.h"
#include <sys/time.h>
#include <errno.h>
#include <time.h>

struct timeval tv;

u64 utime() {
    gettimeofday(&tv, 0);
    return tv.tv_sec * 1000000LU + tv.tv_usec;
}

u64 mtime() {
    gettimeofday(&tv, 0);
    return tv.tv_sec * 1000LU + (tv.tv_usec / 1000);
}

i32 msleep(u64 msec) {
    struct timespec ts;
    i32 res;

    if (msec < 0) {
        errno = EINVAL;
        return -1;
    }

    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;

    do {
        res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);

    return res;
}