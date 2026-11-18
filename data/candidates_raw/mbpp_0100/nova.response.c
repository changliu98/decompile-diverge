int func0(int n) {
    int i, j, k, l, m, p, q, r, s, t, u, v, w, x, y, z;
    char str[1000];

    for (i = n + 1;; i++) {
        if (i > 2147483647)
            break;
        sprintf(str, "%d", i);
        l = strlen(str);
        k = 1;
        for (j = 0, p = 0;; j++) {
            if (p > l / 2)
                break;
            if (str[j]!= str[l - 1 - j]) {
                k = 0;
                break;
            }
            p++;
        }
        if (k) {
            y = i;
            break;
        }
    }
    if (i > 2147483647)
        y = -1;

    return y;
}