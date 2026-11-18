int func0(char *str, char c, int n) {
    int i;
    int ret;

    if (!str) {
        ret = 0;
    } else {
        i = 0;
        while (str[i]) {
            i++;
        }
        if (i >= n - 1) {
            ret = 0;
        } else {
            str[i] = c;
            str[i + 1] = '\0';
            ret = 1;
        }
    }
    return ret;
}