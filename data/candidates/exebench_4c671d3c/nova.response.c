void standardize(int n, long long int *a, long long int *b, long long int *c,
              long long int *x, long long int *y) {
    long long int i = 0;
    while (1) {
        if (i >= 4)
            return;
        if (i < n) {
            *(a + i) = *(x + i);
            *(b + i) = *(y + i);
            *(c + i) = *(x + i);
        } else {
            *(a + i) = 0;
            *(b + i) = 1;
            *(c + i) = 1;
        }
        i++;
    }
}