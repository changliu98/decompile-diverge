char *func0(char *s) {
    int i = 0;
    while (1) {
        if (s[i] == '\0')
            return s;
        if (s[i] =='' || s[i] == ',' || s[i] == '.')
            s[i] = ':';
        i++;
    }
}