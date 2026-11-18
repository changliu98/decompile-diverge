int func0(int n, int k) {
    int i, j, l, m, p, q, r, s, t, x, y, z;

    x = func1(n, k);
    y = sqrt(x);

    z = 0;
    for (i = 1;; i++) {
        if (i > y)
            break;
        if (x % i == 0) {
            z += 2;
            p = i;
            if (p == (x / i))
                z--;
        }
    }

    return z;
}