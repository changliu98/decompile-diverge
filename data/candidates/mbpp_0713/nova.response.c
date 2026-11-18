int func0(char *s, int n) {
    int i = 0;
    char c;
    while (i < n) {
        if (s[i] % 2 == 0) {
            c = 0;
            break;
        }
        i++;
    }
    return c % 2 == 0;
}