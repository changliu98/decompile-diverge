int gcd_ptr(int *a, int *b) {
    while (*a > 0) {
        if (*a < *b) {
            int *temp = a;
            a = b;
            b = temp;
        }
        *a = *a - *b;
    }
    return *b;
}