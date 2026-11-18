char **func0(char *str, int *size) {
    int i, j, k, len;
    char **ret;

    len = strlen(str);
    if (!(ret = (char **)malloc(len * sizeof(char *))))
        ERR("malloc");
    for (i = 0, j = 0, k = 0; i <= len;) {
        if (isspace(str[i]) && str[i] == 0) {
            int l = i - k;
            if (!(ret[j] = (char *)malloc((l + 1) * sizeof(char))))
                ERR("malloc");
            if (ret[j] == NULL)
                exit(1);
            strncpy(ret[j], str + k, l);
            ret[j][l] = '\0';
            k = i + 1;
            j++;
        }
        i++;
    }
    *size = j;
    return ret;
}