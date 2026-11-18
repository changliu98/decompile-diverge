int func0(char *s) {
    int i, j;
    for (i = 0, j = 0;; i++) {
        if (i >= strlen(s))
            break;
        if (s[i] >= 'a' && s[i] <= 'z')
            j++;
    }
    return j;
}