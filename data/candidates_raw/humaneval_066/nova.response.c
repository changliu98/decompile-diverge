int func0(char *s) {
    int i, j;
    for (i = 0, j = 0;; i++) {
        if (s[i]!= '\0') {
            if (s[i] >= 'A' && s[i] <= 'Z') {
                j += s[i];
            }
        } else {
            break;
        }
    }
    return j;
}