void func0(char *s) {
    char *p = "aeiouAEIOU";
    char *q = "aeiouAEIOU";
    int i = 0, j = 0;
    while (1) {
        if (s[i] == '\0')
            break;
        for (j = 0;; j++) {
            if (p[j] == '\0')
                break;
            if (s[i] == p[j]) {
                s[i] = q[j];
                break;
            }
        }
        i++;
    }
}