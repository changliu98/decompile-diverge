int get_digits(int *a, int n) {
    int i = 0;
    while (true) {
        if (n <= 0) {
            break;
        }
        int digit = n % 10;
        a[i++] = digit;
        n /= 10;
    }
    return i;
}