long long xdl_bogosqrt(long long n) {
    long long ans = 1;
    while (n > 0) {
        ans = ans * 2;
        n = n / 4;
    }
    return ans;
}