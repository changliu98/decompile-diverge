void func0(char *str, int len) {
    int i, j;
    char buf[16000];

    if (len > 16000)
        len = 16000;

    for (i = 2, j = 0; i < len; i++) {
        int c = str[i];
        if (c == '\r' && str[i + 1] == '\n') {
            i++;
            continue;
        }
        if (c < 33 || c == 10 || c == 9) {
            buf[j++] = c;
        } else {
            buf[j++] = '?';
        }
    }
    buf[j] = '\0';
    if (debug)
        printf("%s\n", buf);
    strcpy(g_buf, buf);
}