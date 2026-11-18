static char *func0(int n, char *linebuf, int *size) {
    char *token;
    int i = 0;

    token = strtok(linebuf, " \n");
    while (token!= NULL) {
        if (strlen(token) > n) {
            token_list[i++] = token;
        }
        token = strtok(NULL, " \n");
    }
    *size = i;
    return token_list[0];
}