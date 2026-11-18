char *func0(char *str) {
    int len = strlen(str);
    char *res = (char *)malloc(sizeof(char) * (len + 2));
    int i = 0, j = 0, k = 0;
    while (k <= len) {
        if (str[k] =='' || str[k] == '\0') {
            for (int l = 0; l < i - 1; l++) {
                if (l + 1 < i) {
                    if (res[l] > res[l + 1]) {
                        char tmp = res[l];
                        res[l] = res[l + 1];
                        res[l + 1] = tmp;
                    }
                }
            }
            if (i > 0) {
                res[i++] ='';
                for (int l = 0; l < j; l++) {
                    res[i++] = str[j++];
                }
            } else {
                j = 0;
            }
        } else {
            str[j++] = str[k];
        }
        k++;
    }
    res[i] = '\0';
    return res;
}