static void func0(int n, int d, struct timespec *ts) {
    int64_t sec;
    int32_t nsec;

    nsec = n * d;
    sec = nsec / NSEC_PER_SEC;
    nsec %= NSEC_PER_SEC;
    if (sec < INT32_MIN || sec > INT32_MAX) {
        ts->tv_sec = NUM_MAX;
    } else {
        ts->tv_sec = (time_t)sec;
    }
    ts->tv_nsec = nsec;
}