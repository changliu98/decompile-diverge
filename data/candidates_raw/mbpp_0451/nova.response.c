char *func0(char *s) {
    int i = 0, j = 0;
    while (1) {
        if (s[i]!= '\0') {
            if (!isspace(s[i])) {
                s[j++] = s[i];
            }
        } else {
            break;
        }
        i++;
    }
    s[j] = '\0';
    return s;
}