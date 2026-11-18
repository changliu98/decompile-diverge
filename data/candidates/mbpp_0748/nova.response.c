static void func0(char *dir, char *result) {
    regex_t r;
    regcomp(&r, "^[^.]+\\.([0-9]+)$", REG_EXTENDED);
    char *filename;
    char *files[MAX_FILES];
    int i = 0;
    filename = dir;
    result[0] = '\0';
    while (1) {
        if (regexec(&r, filename, 3, files, 0) == 0) {
            strcat(result, filename);
            strcat(result, " ");
            filename = files[1];
        } else {
            strcat(result, filename);
            break;
        }
    }
    regfree(&r);
}