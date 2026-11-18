void xmlrpc_char_encode(char *dest, const char *src) {
    char buf[16];
    mowgli_string_t *str = mowgli_string_create();
    size_t i = 0;

    dest[0] = '\0';

    if (src != NULL && *src != '\0') {
        while (src[i] != '\0') {
            unsigned char c = src[i];

            if (c > 0x7f) {
                snprintf(buf, 16, "&#x%x;", c);
                str->append(str, buf, strlen(buf));
            } else if (c == '&') {
                str->append(str, "&amp;", 5);
            } else if (c == '<') {
                str->append(str, "&lt;", 4);
            } else if (c == '>') {
                str->append(str, "&gt;", 4);
            } else if (c == '"') {
                str->append(str, "&quot;", 6);
            } else {
                str->append_char(str, c);
            }
            i++;
        }
        memcpy(dest, str->str, 0x1000);
    }
}