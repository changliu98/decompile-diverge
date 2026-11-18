void gui_combine_scissor(int *a, int *b) {
    int i, j, k, l, m, n, o, p;
    if (b == NULL)
        return;
    i = a[0];
    j = a[1];
    k = a[0] + a[2];
    l = a[1] + a[3];
    m = b[0];
    n = b[1];
    o = b[0] + b[2];
    p = b[1] + b[3];
    for (i = 0; i < 2; i++) {
        if (a[i] > m)
            k = a[i];
        else
            k = m;
        a[i] = k;
    }
    for (i = 0; a[i + 2] < n; i++) {
        if (a[i + 2] > o)
            l = a[i + 2];
        else
            l = o;
        a[i + 2] = l;
    }
    a[0] = k;
    a[1] = l;
    a[2] = k - i;
    a[3] = l - i;
}