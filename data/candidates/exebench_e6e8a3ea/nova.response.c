int last_slash(char *s, int *p, int *l) {
    int i, j, k;
    i = j = k = 0;
    while (1) {
        if (s[i] == '\0')
            break;
        if (i < 256) {
            if (s[i] == '/') {
                j++;
                k = i;
            }
        }
        i++;
    }
    *p = j;
    *l = i;
    return k;
}