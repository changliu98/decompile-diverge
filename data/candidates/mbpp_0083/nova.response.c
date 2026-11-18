int func0(char *s) {
    int i, j, k;
    for (i = 0, j = 0;; i++) {
        if (s[i] == '\0')
            break;
        j += (s[i] - 'a' + 1);
    }
    if (j % 26 == 0)
        k = 122;
    else
        j = j % 26;
    k = j + 'a' - 1;
    return k;
}