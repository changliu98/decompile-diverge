void logFibonacci(int n, unsigned long *fn1, unsigned long *fn2)
{
    if (n == 2) {
        *fn2 = 1;
        *fn1 = 1;
    } else if (n == 0) {
        *fn2 = 0;
        *fn1 = 0;
    } else {
        int m = n / 2;
        if (m % 2 == 0) {
            logFibonacci(m, fn1, fn2);
            unsigned long f2n = *fn2;
            unsigned long f2n1 = *fn1;
            *fn1 = f2n1 * f2n1 + 2 * f2n * f2n1;
            *fn2 = f2n * f2n + f2n1 * f2n1;
        } else {
            logFibonacci(m - 1, fn1, fn2);
            unsigned long f2n = *fn2;
            unsigned long f2n1 = *fn1;
            *fn2 = f2n1 * f2n1 + 2 * f2n * f2n1;
            *fn1 = f2n * f2n + f2n1 * f2n1 + f2n1 * f2n1;
        }
    }
}