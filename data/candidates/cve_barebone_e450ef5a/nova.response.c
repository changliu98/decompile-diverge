void adjust_skipcol(void) {
    int i, j, k, l, m, n, o, p, q, r, s, t;
    long long int x, y, z;

    while (1) {
        if (!(a[1][1] && a[2][2] && a[3][3]))
            break;
        if (a[1][1] == a[2][2] && a[2][2] == a[3][3])
            break;
        x = a[1][1] - a[2][2];
        y = a[1][1] + a[2][2];
        z = a[1][1] + a[3][3];
        if (z > y)
            break;
        x = z - x;
        for (i = 0; i <= x; i++) {
            if (x < i * z + i)
                break;
        }
        i--;
        a[1][1] = i * z + i;
        a[2][2] = i * z + i;
        a[3][3] = i * z + i;
        break;
    }
    while (1) {
        if (!(a[1][4] && a[2][3] && a[3][2]))
            break;
        if (a[1][4] == a[2][3] && a[2][3] == a[3][2])
            break;
        x = a[1][4] - a[2][3];
        y = a[1][4] + a[2][3];
        z = a[1][4] + a[3][2];
        if (z > y)
            break;
        x = z - x;
        for (i = 0; i <= x; i++) {
            if (x < i * z + i)
                break;
        }
        i--;
        a[1][4] = i * z + i;
        a[2][3] = i * z + i;
        a[3][2] = i * z + i;
        break;