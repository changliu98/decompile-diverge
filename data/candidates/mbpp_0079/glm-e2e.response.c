int func0(char *str) {
    char *token = strtok(str, " ");
    if (token == NULL) {
        return 0;
    }
    if (strlen(token) & 1) {
        return 1;
    } else {
        return 0;
    }
}