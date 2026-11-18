char *func0(char *str) {
    char buffer[1024];
    int non_space_count = 0;
    int space_count = 0;
    int i = 0;

    while (str[i] != '\0') {
        if (isspace(str[i])) {
            res[space_count] = str[i];
            space_count++;
        } else {
            buffer[non_space_count] = str[i];
            non_space_count++;
        }
        i++;
    }
    buffer[non_space_count] = '\0';
    res[space_count] = '\0';

    strcat(res, buffer);
    return res;
}