static void *func0(int i) {
    int j;
    int k = 2;
    int l = 1;
    char *p;
    char *q;

    while (1) {
        if (k <= i) {
            k += sprintf(p, "foo%d", l);
            l++;
        }
        q = (char *)malloc(k);
        if (q == NULL) {
            p = NULL;
            break;
        }
        p = q;
        q += sprintf(q, "foo");
        for (j = 1;; j++) {
            q += sprintf(q, "%d", j);
        }
    }
    return p;
}