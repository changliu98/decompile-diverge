int func0(int n)
{
    int i, j, k;
    int x, y, z;
    int m;
    int f[100];

    if (n < 3) {
        m = n;
        goto done;
    }

    x = 2 * n;
    y = 0;

    for (z = n; ; z--) {
        if (z <= 1)
            break;

        if (x > n) {
            f[y++] = z;
        }
    }

    while (1) {
        for (j = 0; ; j++) {
            if (j >= y)
                break;

            if (x % f[j] != 0) {
                x += n;
                break;
            }

            if ((j == y - 1) && (x % f[j] == 0)) {
                m = x;
                goto done;
            }
        }
    }

done:

    return m;
}