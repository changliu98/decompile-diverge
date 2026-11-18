static char *func0(char *buffer, int pages) {
    char *p;
    char *buffer_end;
    int i;
    int j;
    int k;
    int n;
    int found;

    strcpy(temp_buffer, buffer);

    p = temp_buffer;
    buffer_end = p + strlen(p);

    for (i = 0;; i++) {
        if (i >= pages)
            break;

        found = regexec(&page_regex, p, 1, &n, 0);
        if (found == 0) {
            k = n;
            page_buffer[k] = ':';
        } else
            break;

        p = p + n + 1;
    }

    strcpy(page_buffer, temp_buffer);

    return page_buffer;
}