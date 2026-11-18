char *func0(const char *input) {
    static char buffer[1024]; // Size inferred from typical static buffer allocations, exact size might differ
    regex_t regex;
    regmatch_t match[1];
    int ret;
    const char *p = input;
    char *buf_ptr = buffer;

    ret = regcomp(&regex, " ", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    while (*p != '\0') {
        if (regexec(&regex, p, 1, match, 0) == 0) {
            int len = match[0].rm_eo - match[0].rm_so;
            memcpy(buf_ptr, p, len);
            buf_ptr += len;
            *buf_ptr++ = ' ';
            p += match[0].rm_eo;
        } else {
            strcpy(buf_ptr, p);
            break;
        }
    }

    regfree(&regex);
    return buffer;
}