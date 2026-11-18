int func0(int n) {
    int a[n + 1];
    a[0] = 0;
    a[1] = 1;
    int i = 2;
    while (i <= n + 1) {
        a[i] = i;
        int x = a[i / 2];
        int y = a[i / 3];
        int z = a[i / 4];
        int p = x + y + z;
        if (p > a[i])
            a[i] = p;
        i++;
    }
    return a[n];
}