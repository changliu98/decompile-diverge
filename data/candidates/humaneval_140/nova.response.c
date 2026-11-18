void func0(char *s, char *t) {
    int i = 0, j = 0, state = OUT;
    for (i = 0; i < strlen(s); i++) {
        if (s[i] =='') {
            state++;
        } else if (state == IN) {
            t[j++] = '_';
            if (state == IN) {
                t[j++] = '_';
                t[j++] = '_';
            }
            state = OUT;
        }
        t[j++] = s[i];
    }
    if (state == IN) {
        t[j++] = '_';
        if (state == IN) {
            t[j++] = '_';
            t[j++] = '_';
        }
        state = OUT;
    }
    t[j] = '\0';
}