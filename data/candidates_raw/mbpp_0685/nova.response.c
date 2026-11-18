int func0(int n) {
    int i, j, k, l;
    char a[n + 1];
    for (i = 0; i <= n; i++)
        a[i] = 1;
    for (i = 2; i * i <= n; i++) {
        if (a[i] == 1) {
            for (j = i * 2; j <= n; j += i)
                a[j] = 0;
        }
    }
    int sum = 0;
    for (i = 2; i <= n; i++) {
        if (a[i] == 1)
            sum += i;
    }
    return sum;
}