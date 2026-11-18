void trim(char *s) {
    int i = 0;
    while (1) {
        if (s[i] == '\0') {
            s[i - 1] = '\0';
            break;
        }
        i++;
    }
}