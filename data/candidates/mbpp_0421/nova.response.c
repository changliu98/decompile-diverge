char *func0(char **lines, int nlines) {
    static char error_message[1024];
    strcpy(error_message, "Error: ");
    int i;
    int maxlen = strlen(lines[0]);
    for (i = 0; i < nlines; i++) {
        strcat(error_message, lines[i]);
        if (i < nlines - 1)
            strcat(error_message, ", ");
    }
    return error_message;
}