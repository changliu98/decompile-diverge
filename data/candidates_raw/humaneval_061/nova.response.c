int func0(char *s) {
    int i = 0, j = 0;
    char c;
    while (1) {
        if (j >= strlen(s))
            break;
        if (s[j] == '(')
            i++;
        if (s[j] == ')')
            i--;
        if (i < 0) {
            c = 0;
            break;
        }
        j++;
    }
    if (i % 2 == 1)
        c = 0;
    else
        c = 1;
    return c;
}