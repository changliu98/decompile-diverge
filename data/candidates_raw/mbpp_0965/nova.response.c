char *func0(char *s) {
    int i = 0, j = 0;
    while (s[i]!= '\0') {
        if (isalpha(s[i]) || isblank(s[i])) {
            if (i == 0 || isblank(s[i - 1]) || isblank(s[i - 1]) &&
                isblank(s[i - 2])) {
                u[j++] = '_';
                u[j++] = toupper(s[i]);
            } else {
                u[j++] = s[i];
            }
        }
        i++;
    }
    u[j] = '\0';
    return u;
}