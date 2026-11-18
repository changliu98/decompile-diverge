char **func0(char *str, int *size) {
    int i = 0, j = 0, k = 0, l = 0;
    int len = strlen(str);
    char **arr = NULL;
    char temp[101];
    memset(temp, 0, sizeof(temp));
    while (1) {
        if (strchr(str,'') == NULL && strchr(str, ',') == NULL)
            break;
        arr = (char **)malloc(sizeof(char *) * (len + 1));
        for (i = 0; i < len; i++) {
            if (str[i] =='' || str[i] == ',' || str[i] == '\0') {
                if (i > 0) {
                    temp[i] = '\0';
                    arr[k] = (char *)malloc(sizeof(char) * strlen(temp));
                    strcpy(arr[k++], temp);
                }
                i = 0;
                memset(temp, 0, sizeof(temp));
            } else {
                temp[i] = str[i];
            }
        }
    }
    *size = k;
    return arr;
}