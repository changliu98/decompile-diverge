void logFibonacci(int n, long long *x, long long *y) {
    if (n == 2) {
        *x = 1;
        *y = 1;
    } else if (n == 0) {
        *x = 0;
        *y = 0;
    } else {
        int m = n / 2;
        if (m % 2 == 0) {
            logFibonacci(m, x, y);
            long long a = *y * 2 + *x * 2;
            long long b = *x * 2 + *y * 2;
            *x = a;
            *y = b;
        } else {
            logFibonacci(m - 1, x, y);
            long long a = *y * 2 + *x * 2;
            long long b = *x * 2 + *y * 2;
            *y = a;
            *x = b;
        }
    }
}