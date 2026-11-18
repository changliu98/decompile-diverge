int _gd2GetHeader(char *s, char *s1, char *s2, char *s3, char *s4, char *s5) {
    int i, j, k, l, m, n;
    char *p, *q, *r, *t;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 256; j++) {
            if (strcmp(s, s1) == 0)
                break;
            if (strcmp(s, s2) == 0)
                break;
            if (strcmp(s, s3) == 0)
                break;
            if (strcmp(s, s4) == 0)
                break;
            if (strcmp(s, s5) == 0)
                break;
            if (strcmp(s1, s) == 1)
                break;
            if (strcmp(s2, s) == 1)
                break;
            if (strcmp(s3, s) == 1)
                break;
            if (strcmp(s4, s) == 1)
                break;
            if (strcmp(s5, s) == 1)
                break;
        }
    }
    l = strlen(s1) * strlen(s2);
    p = (char *)calloc(l, sizeof(char));
    for (i = 0; i < l; i++) {
        if (strcmp(p + i, s) == 1)
            break;
        if (p[i][1] < 0 && p[i][2] < 0)
            break;
        if (p[i][1] > 0 && p[i][2] > 0)
            break;
    }
    *s1 = p;
    return 1;
}