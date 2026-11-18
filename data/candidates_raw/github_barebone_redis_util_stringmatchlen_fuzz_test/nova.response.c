int func0() {
    int i, j, k, l, m, n;
    char buf[32];
    int res = 0;

    while (1) {
        k = rand() % (MAX_K - 1);
        l = rand() % (MAX_K - 1);
        for (i = 0; i < k; i++)
            buf[i] = rand() % (MAX_CHAR - '0');
        for (i = 0; i < l; i++)
            buf[i] = rand() % (MAX_CHAR - '0');

        res += test(buf, l, buf, k, 0);
    }

    return res;
}