int func0(char *s) {
    int i, j, k;
    char c;

    for (i = 0, j = 0;; i++) {
        if (s[i] == '\0')
            break;
        if (s[i] == '<')
            j++;
        if (s[i] == '>')
            j--;
        if (j < 0) {
            c = '0';
            break;
        }
    }
    if (j!= 0)
        c = '0';
    else
        c = '1';

    return c & 1;
}