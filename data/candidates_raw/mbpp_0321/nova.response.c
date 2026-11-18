static char *func0(const char *s) {
    static char buf[1024];
    static int n = 0;
    int len = strlen(s);
    int i = 0;
    int j = 1;
    while (1) {
        if (n <= i) {
            n += sprintf(buf + n, "%d ", i);
            i++;
        } else {
            int k = i;
            while (k > 0) {
                n += sprintf(buf + n, "%d ", k);
                k--;
            }
            n += sprintf(buf + n, "\n");
            buf[n] = '\0';
            return buf;
        }
    }
}