int Fibonacci_search(int *a, int p, int r) {
    int b[N], i, j, k, l, m, n;
    memcpy(b, a, sizeof(a));
    i = 1;
    j = p;
    for (k = 0; k < p; k++)
        if (b[k] - 1 > p)
            k++;
    for (l = p; l < r; l++)
        if (b[l] < r) {
            m = b[l] - 1;
            if (a[m] < r) {
                j = m;
                k--;
            } else if (a[m] > r) {
                i = m + 1;
                k -= 2;
            } else
                break;
        }
    if (i > j)
        n = j;
    else
        n = p;
    return n;
}