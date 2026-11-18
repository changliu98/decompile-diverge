static char *func0(char *format) {
    char *fmt = format;
    char *fmt_buf = fmt_buf;
    regex_t re;
    regmatch_t pmatch;
    int nmatch = 1;

    if (regcomp(&re, "%%[0-9]*[hl]?[c|d|o|x|X|u|a|A|e|E|f|F|g|G|i|n|p|s|y|Y]",
                REG_EXTENDED)) {
        fmt_buf = NULL;
        return fmt_buf;
    }

    while (1) {
        if (*fmt == '\0') {
            break;
        }
        if (regexec(&re, fmt, nmatch, &pmatch, 0) == 0) {
            memcpy(fmt_buf, fmt, pmatch.rm_eo);
            fmt_buf += pmatch.rm_eo;
            *fmt_buf++ ='';
            fmt += pmatch.rm_eo + pmatch.rm_so;
        } else {
            strcpy(fmt_buf, fmt);
            break;
        }
    }
    regfree(&re);
    fmt_buf = fmt_buf_tmp;
    return fmt_buf;
}