int func0(int n) {
    int a[n + 1], i;
    a[0] = 0;
    a[1] = 1;
    for (i = 2; i <= n;) {
        int x = a[i / 2];
        int y = a[i / 3];
        a[i] = x + y;
        if (a[i] < i)
            a[i] = i;
        i++;
    }
    return a[n];
}