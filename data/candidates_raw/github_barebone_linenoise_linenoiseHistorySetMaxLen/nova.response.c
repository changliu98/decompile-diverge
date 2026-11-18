int func0(int n) {
    int i, j;
    int *tmp;

    if (n < 2) {
        return 0;
    }

    if (p) {
        i = m;
        tmp = (int *)malloc(n * sizeof(int));
        if (tmp == NULL) {
            return 0;
        }

        for (j = 0; j < n; j++) {
            if (j < i - n) {
                free(p[j]);
            } else {
                i = n;
                memcpy(tmp, p[j], n * sizeof(int));
            }
        }
        memcpy(p + j - i, tmp, i * sizeof(int));
        free(tmp);
        p[j - i] = NULL;
        m = i;
        if (m > max) {
            max = m;
        }
    }
    return 1;
}