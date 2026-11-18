char *func0(char *str) {
    char *p, *q;
    int i, flag;
    if (str == NULL) {
        return NULL;
    }
    p = q = (char *)malloc(strlen(str) + 1);
    if (q == NULL) {
        return NULL;
    }
    for (i = 0;; i++) {
        if (str[i] == '\0') {
            break;
        }
        if (str[i]!='') {
            *q++ = str[i];
            flag = 0;
        } else if (flag == 0) {
            *q++ ='';
            flag = 1;
        }
    }
    *q = '\0';
    return p;
}