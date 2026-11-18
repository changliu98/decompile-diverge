int func0(char *str) {
    char *token = strtok(str, " ");
    int result;

    if (token != NULL) {
        if (strlen(token) % 2 == 0) {
            result = 1;
        } else {
            result = 0;
        }
    } else {
        result = 0;
    }

    return result;
}