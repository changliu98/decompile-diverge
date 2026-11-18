int func0(int *a, int n) {
    int i, sum = 0;
    for (i = 0; i < n; i++) {
        sum = sum * 10 + a[i];
    }
    return sum;
}