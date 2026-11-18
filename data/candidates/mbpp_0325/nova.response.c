int func0(int n) {
    int i, j, k, l, m, p, q, r, s, t, x, y, z;
    if (n <= 3)
        return n;
    x = n;
    for (i = 1;; i++) {
        y = i * i;
        if (y > n)
            break;
        for (j = i;; j++) {
            z = y + j * j;
            if (z > n)
                break;
            if (z <= n)
                p = z;
            else
                p = z - j * j;
            q = n - y + j * j;
            r = sqrt(q) + 1;
            if (p < r)
                x = p;
            else
                x = r;
        }
    }
    return x;
}