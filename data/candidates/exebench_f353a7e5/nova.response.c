void strip(char *str) {
    if (str == NULL)
        return;
    int i, j, k;
    for (i = 1; str[i]!= '\0'; i++) {
        if (str[i] == '\0')
            break;
        for (j = 0; j < i; j++) {
            if (str[j] == str[i]) {
                str[i] = -1;
                break;
            }
        }
    }
    for (k = 0, j = 0;; k++) {
        if (str[k] == '\0')
            break;
        if (str[k] == -1)
            continue;
        else {
            j = k;
            while (str[j]!= -1)
                j++;
            str[k] = str[j];
            str[j] = -1;
        }
    }
    str[k] = '\0';
}