char *func0(int p, int q, int r, int s) {
    int i = 0;
    char *str;
    if (p > 0)
        i += p;
    if (q > 0)
        i += q;
    if (r > 0)
        i += r;
    if (s > 0)
        i += s;
    str = (char *)malloc((i + 1) * sizeof(char));
    if (str == NULL) {
        printf("malloc error");
        exit(1);
    }
    int j = 0;
    for (int k = 0; k < p; k++) {
        str[j++] = 'p';
    }
    for (int k = 0; k < q; k++) {
        str[j++] = 'q';
    }
    for (int k = 0; k < r; k++) {
        str[j++] = 'r';
    }
    for (int k = 0; k < s; k++) {
        str[j++] ='s';
    }
    str[j] = '\0';
    return str;
}