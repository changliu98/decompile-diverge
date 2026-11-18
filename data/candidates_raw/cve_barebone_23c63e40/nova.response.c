char *func0(FILE *f, char *line) {
    char *p;
    char *q;

    p = fgets(line, MAX_LINE_LENGTH, f);
    if (p == NULL) {
        return NULL;
    }

    q = line;
    if (line[strlen(line) - 1] == '\n') {
        line[strlen(line) - 1] = '\0';
    }

    return p;
}