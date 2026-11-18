int func0(char *s, char *t) {
    int i, j;
    for (i = 0;; i++) {
        for (j = 0;; j++) {
            if (s[i] == '\0')
                return j;
            if (t[j] == '\0')
                break;
            if (s[i] == t[j])
                break;
        }
    }
}