char *my_strupcase(char *str) {
    char *p;
    int i;

    if (str == NULL) {
        p = NULL;
    } else {
        for (i = 0;; i++) {
            if (str[i] == '\0') {
                break;
            }
            if (str[i] >= 'a' && str[i] <= 'z') {
                str[i] = str[i] - 32;
            }
        }
        p = str;
    }
    return p;
}