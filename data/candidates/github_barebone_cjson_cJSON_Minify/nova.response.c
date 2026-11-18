void cJSON_Minify(char *s) {
    char *b = s;
    if (!s)
        return;
    while (*s) {
        if (!*s ||!isspace(*s)) {
            while (*s && isspace(*s))
                s++;
            if (*s == '/' && *(s + 1) == '/') {
                skip_line(&s);
                continue;
            }
            if (*s == '/' && *(s + 1) == '*') {
                skip_comment(&s);
                continue;
            }
            if (*s == '\"') {
                skip_quote(&s, &b);
                continue;
            }
            *b++ = *s++;
        } else {
            s++;
        }
    }
    *b = '\0';
}