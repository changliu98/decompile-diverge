void ceasar(char *str, char c) {
    int i = 0;
    int j = 0;
    for (i = 0;; i++) {
        if (str[i] == '\0')
            break;
        if ((str[i] >= 'A' && str[i] <= 'Z') ||
            (str[i] >= 'a' && str[i] <= 'z')) {
            for (j = 0;; j++) {
                if (j >= c)
                    break;
                if (str[i] == 'Z') {
                    str[i] = 'A';
                    str[i]--;
                } else if (str[i] == 'z') {
                    str[i] = 'a';
                    str[i]--;
                }
                str[i]++;
            }
        }
    }
}