char *func0(int n) {
    int i, j, k, l, m, p, q, r, s, t, u, v, w, x, y, z;
    char *a;
    i = j = k = l = m = p = q = r = s = t = u = v = w = x = y = z = 0;
    i = n;
    while (1) {
        k = sqrt(i);
        if (k + 2 <= l) {
            if (i % l == 0) {
                if (i / l == l) {
                    p = p + 1;
                } else {
                    p = p + 2;
                }
            }
        } else {
            l = l + 1;
        }
    }
    if (p % 2 == 0) {
        a = "Prime";
    } else {
        a = "Not Prime";
    }
    return a;
}