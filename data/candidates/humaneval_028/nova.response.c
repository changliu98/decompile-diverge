char *func0(char *args[], int arg_size) {
    int i, j, len = 0;
    for (i = 0; i < arg_size; i++)
        len += strlen(args[i]);

    char *str = (char *)malloc(sizeof(char) * (len + 1));
    if (str == NULL) {
        str = NULL;
    } else {
        str[0] = '\0';
        for (j = 0; j < arg_size; j++)
            strcat(str, args[j]);
    }
    return str;
}