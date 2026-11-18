char func0(char *s) {
    int len = strlen(s);
    int i = 0;
    char c;
    while (i < len) {
        char cur = s[i];
        int j = 0;
        int k = 0;
        while (k <= i) {
            if (s[k] == cur) {
                j++;
            }
            k++;
        }
        if (j > 1) {
            c = cur;
            break;
        }
        i++;
    }
    if (i < len) {
        return c;
    } else {
        return '0';
    }
}