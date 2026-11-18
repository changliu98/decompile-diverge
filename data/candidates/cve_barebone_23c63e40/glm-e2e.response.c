char *get_next_file(char *buf, FILE *fp) {
    char *ret = fgets(buf, 1024, fp);
    if (ret == NULL) {
        return NULL;
    }
    
    // Strip the trailing newline character if it exists
    size_t len = strlen(buf);
    if (len > 0 && buf[len - 1] == '\n') {
        buf[len - 1] = '\0';
    }
    
    return ret;
}