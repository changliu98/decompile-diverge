char *func0(char *s, int n) {
    char buf[1000];
    strncpy(buf, s, 1000);
    buf[1000 - 1] = '\0';
    char *p = strdup(buf);
    if (p == NULL) {
        perror("strdup");
        exit(1);
    }
    *p = '\0';
    char *q = strtok(buf, " \t\n");
    while (q!= NULL) {
        if (strlen(q)!= n) {
            strcat(p, q);
            strcat(p, " ");
        }
        q = strtok(NULL, " \t\n");
    }
    size_t len = strlen(p);
    if (len > 0 && p[len - 1] =='') {
        p[len - 1] = '\0';
    }
    return p;
}