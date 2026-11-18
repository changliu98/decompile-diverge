int func0(int n, int i, int j, int k) {
    int a[n + 10], x, y, z;
    for (x = 0; x < n + 10; x++)
        a[x] = -1;
    a[0] = 0;
    for (x = 0; x < n + 10;) {
        if (a[x] == -1)
            x++;
        else {
            if (x + i <= n)
                y = a[x] + 1;
            else
                y = a[x];
            a[x + i] = y;
        }
        if (x + j <= n + 10)
            a[x + j] = a[x] + 1;
        if (x + k <= n + 10)
            a[x + k] = a[x] + 1;
    }
    return a[n];
}