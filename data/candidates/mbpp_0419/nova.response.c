int func0(double *a, int n) {
    int i, sum = 0;
    for (i = 0; i < n; i++)
        sum += round(a[i]);
    return sum * n;
}