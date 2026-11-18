int func0(int n) {
    int a = n, i = 0, j, k, l, m, b[100];
    while (a > 0) {
        b[i++] = a % 10;
        a /= 10;
    }
    for (j = 0, k = i - 1; j < k; j++, k--) {
        m = b[j];
        b[j] = b[k];
        b[k] = m;
    }
    for (l = 0, m = i; l < n; l++) {
        if (m <= i - 1)
            l += b[l];
        else
            l += b[l - i];
    }
    return (l == n)? 1 : 0;
}