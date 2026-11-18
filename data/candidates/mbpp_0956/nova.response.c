char **func0(char *str, int *size) {
    int i, j, len = strlen(str);
    char **res = (char **)malloc(sizeof(char *) * len);
    *size = 0;
    for (i = 0, j = 1; j <= len;) {
        if (j == len || isspace(str[j]) || isspace(str[j - 1])) {
            int wordlen = j - i;
            res[*size] = (char *)malloc(sizeof(char) * (wordlen + 1));
            strncpy(res[*size], str + i, wordlen);
            res[(*size)++][wordlen] = '\0';
            i = j + 1;
        }
        j++;
    }
    return res;
}