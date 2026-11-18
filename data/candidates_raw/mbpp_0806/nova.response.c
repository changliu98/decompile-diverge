int func0(char *s) {
    int i, j, k, l, max = 0, max_t = 0;
    l = strlen(s);
    for (i = 0; i < l; i++) {
        if (isalpha(s[i])) {
            if (max + 1 > max_t)
                max_t = max + 1;
            max = 0;
        } else {
            max++;
        }
    }
    if (isalpha(s[l - 1])) {
        if (max > max_t)
            max_t = max;
    }
    return max_t;
}