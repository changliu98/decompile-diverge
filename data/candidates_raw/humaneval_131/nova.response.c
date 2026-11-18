int func0(int n) {
    int i, j, k, l, m, p, q;
    i = 1;
    p = 0;
    while (n > 0) {
        j = n % 10;
        if (j % 2 == 1) {
            p = 1;
            i = i * j;
        }
        n = n / 10;
    }
    if (p)
        k = i;
    else
        k = 0;
    return k;
}