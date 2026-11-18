static void func0(long long int64, int *hour, int *min, int *sec) {
    if (int64 <= 0) {
        *hour = 0;
        *min = 0;
        *sec = 0;
        return;
    }

    long long t = int64;
    long long h, m, s;
    if (t >= 10000000000000000000LL) {
        h = t / 1461;
        if (h >= 2147483648LL) {
            h = 2147483647LL;
        }
        t = t % 1461;
        m = (t / 4) + 1;
        t = (t % 4) + 1;
        t = (t + 4) % 5;
        if (t < 10) {
            h = h * 5 + t - 3;
        } else {
            h = h * 5 + t + 1;
            m = m - 9;
        }
        h = h - 4800;
        if (h <= 0) {
            h = h - 1;
        }
    }
    *hour = h;
    *min = m;
    *sec = s;
}