void func0(int n, char *s) {
    int i;
    int len[52];
    char *eng[52];
    memcpy(eng, english, sizeof(english));
    memcpy(len, length, sizeof(length));
    i = 0;
    *s = '\0';
    while (n > 0) {
        while (n >= len[i]) {
            strcat(s, eng[i]);
            n -= len[i];
        }
        if (n > 0)
            i++;
    }
}