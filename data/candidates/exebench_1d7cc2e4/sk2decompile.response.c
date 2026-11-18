void logFibonacci(int n, unsigned long long *a, unsigned long long *b) {
  if (n == 2) {
    *b = 1;
    *a = 1;
    return;
  }
  if (n == 0) {
    *b = 0;
    *a = 0;
    return;
  }
  int k = n / 2;
  if (k % 2 == 0) {
    logFibonacci(k, a, b);
    unsigned long long a1 = *a * *a;
    unsigned long long b1 = *b * *b;
    *a = a1 + (2 * *b) * *a;
    *b = a1 + b1;
  } else {
    logFibonacci(k - 1, a, b);
    unsigned long long a1 = *a * *a;
    unsigned long long b1 = (2 * *b) * *a;
    *b = a1 + b1 + *b * *b;
    *a = a1 + b1;
  }
}