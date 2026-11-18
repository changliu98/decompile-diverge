int func0(char *s) {
    int i, j, k;
    char *p;

    p = s;
    while (*p =='')
        p++;

    for (i = 0;; i++) {
        if (i >= strlen(p))
            break;
        if (p[i] =='') {
            k = 0;
            continue;
        }
        k++;
    }

    return k;
}