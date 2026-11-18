int func0(int x) {
    int i, j, k, l, m, n;

    if (x % 2)
        n = (x + 1) / 2;
    else {
        m = 0;
        for (i = 0; i < 32; i++)
            m += (x >> i) & 1;
        n = x / 2;
        if (m % 2)
            n++;
    }

    return n;
}