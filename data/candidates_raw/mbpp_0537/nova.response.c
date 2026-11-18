char *func0(char *s) {
    char *p, *q, *r, *t;
    int i, j;
    static char result[80];

    p = strtok(s, " ");
    for (i = 0; p!= NULL; p = strtok(NULL, " ")) {
        for (j = 0; j < i; j++) {
            if (strcmp(result, p) == 0) {
                r = p;
                goto found;
            }
        }
        result[i++] = p;
    }
    r = result;
found:
    return r;
}