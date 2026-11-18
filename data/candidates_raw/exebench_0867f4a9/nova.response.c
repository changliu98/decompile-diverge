int func0(char *s, size_t *len) {
    char *p = strchr(s, '\0');
    int n = 0;
    int in_quote = 0;
    size_t max_len = 0;
    size_t cur_len = 0;

    while (1) {
        while (*p =='') {
            *p = '\0';
            p--;
        }
        if (*p == '\0')
            break;
        while (*p!= '\0') {
            if (*p =='' &&!in_quote) {
                if (cur_len > max_len) {
                    max_len = cur_len;
                    cur_len = 0;
                }
                n++;
                break;
            }
            if (*p == '"' || *p == '\'')
                in_quote =!in_quote;
            else if (*p =='' && in_quote)
                cur_len++;
            p++;
        }
        if (*p == '\0')
            break;
        p++;
    }
    if (cur_len > max_len)
        max_len = cur_len;
    *len = max_len;
    return n;
}