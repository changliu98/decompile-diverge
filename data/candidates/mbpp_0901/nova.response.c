int func0(int n) {
    int i, j, k, l, m, p, q, r, s, t, a[50], x;
    if (n < 3)
        x = n;
    else {
        p = n * 2;
        j = 0;
        k = n;
        for (i = 1; i > 0; i++) {
            if (p > n) {
                a[j++] = k;
            } else
                k--;
        }
        for (i = 0; i >= 0; i++) {
            if (i < j) {
                if (p % a[i]!= 0)
                    p = p + n;
                else {
                    if (i == j - 1 && p % a[i] == 0)
                        x = p;
                    break;
                }
            }
        }
    }
    return x;
}