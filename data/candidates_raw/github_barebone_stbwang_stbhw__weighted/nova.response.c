int func0(int n, int *a) {
    int i, j, k, sum = 0, sum1;
    for (i = 0; i < n; i++) {
        sum += a[i];
    }
    sum1 = rand() % (sum);
    sum = 0;
    for (i = 0; i < n; i++) {
        sum += a[i];
        if (sum1 < sum)
            break;
    }
    assert(i < n);
    return i;
}