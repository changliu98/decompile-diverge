char *func0(char *s) {
    int len = strlen(s);
    int i = 0, j = 0, k = 0, l = -1;
    while (i < len) {
        if (s[i] =='') {
            if (j % 2 == 0) {
                if (k < j) {
                    k = j;
                    l = i - k;
                }
            } else {
                j = 0;
            }
        } else {
            j++;
        }
        i++;
    }
    if (j % 2 == 0) {
        if (k < j) {
            k = j;
            l = i - k;
        }
    }
    if (l == -1) {
        char *p = "NO";
        return p;
    }
    strncpy(s1, s + l, k);
    s1[k] = '\0';
    char *p = s1;
    return p;
}