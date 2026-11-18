char *func0(char *s, char *t) {
    int i, j, k;
    char *p;
    int *next;

    next = getNext(t);
    i = 0;
    j = 0;
    p = (char *)malloc(strlen(s) * sizeof(char));
    while (s[i]!= '\0') {
        while (j!= -1 && t[j]!= s[i])
            j = next[j];
        j++;
        p[i] = s[i];
        i++;
    }
    p[i] = '\0';
    return p;
}