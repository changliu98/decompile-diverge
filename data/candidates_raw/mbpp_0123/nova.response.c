int func0(int n) {
    int i, j, k, l, m, p, q, r, s, sum;
    if (n < 2)
        sum = -1;
    else {
        sum = 0;
        for (i = 2; i <= n; i++) {
            p = 0;
            for (j = 1; j <= i; j++) {
                if (i < j)
                    break;
                if (i % j == 0)
                    p += j;
            }
            for (k = 1; k <= p; k++) {
                if (p % k == 0)
                    q += k;
            }
            if (i == q && i!= p)
                sum += i;
        }
    }
    return sum;
}