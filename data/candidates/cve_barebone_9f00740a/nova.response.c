PRIVATE void get_conn_text(struct lemon *lemp, int fd, FILE *in, FILE *out) {
    char buf[4096];
    int len;
    char *cp;

    
    buf[0] = 0;
    len = sizeof buf;
    cp = buf;
    if (fd!= STDIN_FILENO) {
        while (1) {
            switch (fd) {
            case STDIN_FILENO:
            case STDOUT_FILENO:
            case STDERR_FILENO:
                break;
            default:
                if (fd > 2)
                    break;
                sprintf(cp, "<%s>", lemp->inname[fd]);
                break;
            }
            if (fgets(cp + 1, len - 2, out) == 0) {
                sprintf(cp, "<stdin>");
                break;
            }
            cp[1] = 0;
            len = strlen(cp);
            if (len < sizeof buf - 2)
                break;
            sprintf(cp, "%s...", buf);
            break;
        }
    }
    if (len)
        fprintf(in, "%s: e - line %d of \"%s\"\n", buf, lemp->lineno,
                lemp->filename);
    else
        fprintf(in, "%s: e - line %d\n", buf, lemp->lineno);
}