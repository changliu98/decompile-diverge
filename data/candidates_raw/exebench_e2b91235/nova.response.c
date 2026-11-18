int func0(int *a, int n) {
    int i = 0;
    while (n > 0) {
        a[i++] = n % 10;
        n /= 10;
    }
    return i;
}