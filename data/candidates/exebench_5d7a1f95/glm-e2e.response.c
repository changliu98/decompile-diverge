void escape(char *dst, const char *src) {
    int j = 0;
    for (int i = 0; src[i] != '\0'; i++) {
        switch (src[i]) {
            case '\a': dst[j++] = '\\'; dst[j++] = 'a'; break;
            case '\b': dst[j++] = '\\'; dst[j++] = 'b'; break;
            case '\f': dst[j++] = '\\'; dst[j++] = 'f'; break;
            case '\n': dst[j++] = '\\'; dst[j++] = 'n'; break;
            case '\r': dst[j++] = '\\'; dst[j++] = 'r'; break;
            case '\t': dst[j++] = '\\'; dst[j++] = 't'; break;
            case '\v': dst[j++] = '\\'; dst[j++] = 'v'; break;
            case '\\': dst[j++] = '\\'; dst[j++] = '\\'; break;
            case '\?': dst[j++] = '\\'; dst[j++] = '?'; break;
            case '\'': dst[j++] = '\\'; dst[j++] = '\''; break;
            case '\"': dst[j++] = '\\'; dst[j++] = '\"'; break;
            default:
                dst[j++] = src[i];
                break;
        }
    }
    dst[j] = '\0';
}