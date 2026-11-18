char *func0(char *s) {
    static char u[80];
    int i;

    for (i = 0;; i++) {
        if (s[i] == 0)
            break;
        u[i] = toupper(s[i]);
    }
    u[i] = 0;
    return (u);
}