char *func0(char *s, char *t) {
    int i = 0, j = 0;
    for (;;) {
        if (j < strlen(s)) {
            if (!isspace(s[j]))
                t[i++] = s[j];
        } else
            break;
        j++;
    }
    t[i] = '\0';
    return t;
}