char **func0(char *str) {
    int i = 1, j = 0;
    char *p = str;
    char **arr;
    char *temp;
    while (1) {
        if (*p == '\0')
            break;
        if (*p =='')
            i++;
        p++;
    }
    arr = (char **)malloc(sizeof(char *) * (i + 1));
    if (arr == NULL) {
        arr = NULL;
        return arr;
    }
    p = strdup(str);
    if (p == NULL) {
        free(arr);
        arr = NULL;
        return arr;
    }
    i = 0;
    while (1) {
        temp = strsep(&p, " ");
        if (temp == NULL)
            break;
        arr[i++] = strdup(temp);
    }
    arr[i] = NULL;
    free(p);
    return arr;
}