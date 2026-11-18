void foo(long n, long *a, long *b) {
    if (n > 0) {
        foo(n / 2, a, b);
        for (long i = 1; i <= n; i++) {
            *a += *b;
        }
    }
}