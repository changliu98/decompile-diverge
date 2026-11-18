int get_digits(int *a, int n) {
    int i = 0;
    while (1) {
        if (n == 0) break;
        a[i] = n % 10;
        n /= 10;
        i++;
    }
    return i;
}