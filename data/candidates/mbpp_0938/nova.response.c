void func0(int *a, int *b, int *c, int n, int m, int k) {
    int i, j, l, x, y, z, min, max;
    while (1) {
        min = INT_MAX;
        max = 0;
        for (i = 0; i < n; i++) {
            for (j = 0; j < m; j++) {
                for (l = 0; l < k; l++) {
                    if (a[i] > b[j] && a[i] > c[l]) {
                        max = a[i];
                    } else if (b[j] > c[l]) {
                        max = b[j];
                    } else {
                        max = c[l];
                    }
                    if (max - min < min) {
                        min = max - min;
                        x = i;
                        y = j;
                        z = l;
                    }
                }
            }
        }
        if (min == 0) {
            break;
        }
        if (a[x] == max) {
            i = x + 1;
        }
        if (b[y] == max) {
            j = y + 1;
        }
        if (c[z] == max) {
            l = z + 1;
        }
    }
    a[0] = a[x];
    b[0] = b[y];
    c[0] = c[z];
}