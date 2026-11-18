char *func0(char *s) {
    char *p;
    char *list[MAX_LINES];
    int i = 0;

    p = strtok(s, " ");
    while (p) {
        list[i++] = p;
        p = strtok(NULL, " ");
    }
    list[i] = NULL;

    int j = i - 1;
    while (j >= 0) {
        strcat(buf, list[j]);
        if (j > 0)
            strcat(buf, " ");
        j--;
    }
    return buf;
}