char *func0(char *s1, char *s2) {
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    int i, j;
    int len;
    char *s;

    if (len1 < len2)
        len = len1;
    else
        len = len2;

    s = (char *)malloc((len + 1) * sizeof(char));
    if (s == NULL) {
        return NULL;
    }

    for (i = 0; i < len + 1; i++) {
        if (i < len) {
            if (s1[i] == s2[i])
                s[i] = '1';
            else
                s[i] = '0';
        } else
            s[i] = '\0';
    }
    return s;
}