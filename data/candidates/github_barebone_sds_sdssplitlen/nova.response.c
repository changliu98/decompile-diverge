char **sdssplitlen(char *str, char *delimit, char *token, int count,
                   int *num) {
    char **buf;
    int i = 0, j = 0, k = 0;
    char *p = NULL;
    int len = 5;
    if (count < 2 || delimit == NULL) {
        *num = 0;
        for (i = 0;; i++) {
            if (str[i] == '\0') {
                break;
            }
        }
        return NULL;
    }
    while (1) {
        buf = (char **)malloc(sizeof(char *) * len);
        if (buf == NULL) {
            break;
        }
        for (i = 0; i < count - 1; i++) {
            if (len <= i) {
                len *= 2;
                buf = (char **)realloc(buf, sizeof(char *) * len);
                if (buf == NULL) {
                    break;
                }
            }
            p = str + i;
            for (j = i;; j++) {
                if (str[j] == '\0') {
                    break;
                }
                if (strchr(delimit, str[j])!= NULL) {
                    buf[k] = (char *)malloc(sizeof(char) * (j - i));
                    if (buf[k] == NULL) {
                        break;
                    }
                    strncpy(buf[k], p, j - i);
                    if (buf[k] == NULL) {
                        break;
                    }
                    k++;
                    i = j;
                    p = str + j + 1;
                    break;
                }
            }
        }
        *num = k;
        return buf;
    }
    *num = 0;
    return NULL;
}