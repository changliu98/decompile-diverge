char **func0(const char *txt, int *returnSize) {
    int i, j = 0, num = 0, count = 0;
    int len = strlen(txt);
    char **out = NULL;
    char current[101] = {0};

    if (strchr(txt, ' ') || strchr(txt, ',')) {
        out = malloc(sizeof(char *) * (len + 1));
        for (i = 0; i <= len; ++i) {
            if (txt[i] == ' ' || txt[i] == ',' || txt[i] == '\0') {
                if (j > 0) {
                    current[j] = '\0';
                    out[count] = strdup(current);
                    count++;
                    j = 0;
                }
            } else {
                current[j++] = txt[i];
            }
        }
    } else {
        for (i = 0; i < len; ++i) {
            if (islower(txt[i]) && ((txt[i] - 'a') % 2 == 1)) {
                num++;
            }
        }

        out = malloc(sizeof(char *));
        out[0] = malloc(sizeof(char) * 12);
        sprintf(out[0], "%d", num);
        count = 1;
    }

    *returnSize = count;
    return out;
}