int func0(int *a, int n) {
    int i, j, k, l, m, p, q, r, s, t, u, v, w, x, y, z, aa, bb, cc, max, min, sum,
        flag;

    max = 1;
    min = 1;
    sum = 0;
    flag = 0;
    for (i = 0; i < n; i++) {
        if (a[i] > 0) {
            sum = sum * a[i];
            if (a[i] * a[i] < 2)
                y = a[i];
            else
                y = 1;
        } else {
            if (a[i] == 0) {
                max = 1;
                min = 1;
            } else {
                z = sum;
                if (a[i] * a[i] < 2)
                    y = a[i];
                else
                    y = 1;
                sum = z * a[i];
            }
        }
        flag = 1;
    }
    if (flag == 0 && sum == 0)
        y = 0;
    else
        y = sum;
    return y;
}