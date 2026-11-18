char* func0(int num, int n) {
    static char xs[100];
    char buf[80];
    int len;
    int i;
    char c;

    sprintf(xs, "%d", num);
    len = strlen(xs);

    if (len < n) {
        // Reverse the string
        for (i = 0; i < len / 2; i++) {
            c = xs[i];
            xs[i] = xs[len - 1 - i];
            xs[len - 1 - i] = c;
        }
    } else {
        // Rotate right by n
        strcpy(buf, xs + len - n);
        buf[n] = '\0';
        strncat(buf, xs, len - n);
        strcpy(xs, buf);
    }

    return xs;
}