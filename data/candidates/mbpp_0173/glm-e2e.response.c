char *func0(char *str) {
    int i = 0;
    int j = 0;
    int len = strlen(str);
    char buffer[len + 1];

    while (str[i] != '\0') {
        if (isdigit((unsigned char)str[i])) {
            buffer[j] = str[i];
            j++;
        }
        i++;
    }
    buffer[j] = '\0';
    strcpy(str, buffer);
    return str;
}