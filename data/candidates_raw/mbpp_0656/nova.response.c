int func0(int *a, int *b, int n) {
    int i, ret;

    sort(a, n);
    sort(b, n);

    ret = 0;
    for (i = 0; i < n; i++)
        ret += abs(a[i] - b[i]);

    return ret;
}