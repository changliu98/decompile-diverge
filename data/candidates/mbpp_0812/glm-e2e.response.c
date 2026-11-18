char* func0(char* str) {
    int len = strlen(str);
    if (len > 4) {
        if (strcmp(str + len - 4, "ABCD") == 0) {
            str[len - 4] = '\0';
            strcat(str, "EFGH");
        }
    }
    return str;
}