void unescape(char *dst, const char *src) {
    int j = 0;
    int i = 0;
    
    while (src[i] != '\0') {
        if (src[i] == '\\') {
            i++;
            switch (src[i]) {
                case 'a':  dst[j] = '\a'; break;
                case 'b':  dst[j] = '\b'; break;
                case 'f':  dst[j] = '\f'; break;
                case 'n':  dst[j] = '\n'; break;
                case 'r':  dst[j] = '\r'; break;
                case 't':  dst[j] = '\t'; break;
                case 'v':  dst[j] = '\v'; break;
                case '?':  dst[j] = '?';  break;
                case '\\': dst[j] = '\\'; break;
                case '\'': dst[j] = '\''; break;
                case '"':  dst[j] = '"';  break;
                default:
                    dst[j] = '\\';
                    j++;
                    dst[j] = src[i];
                    break;
            }
        } else {
            dst[j] = src[i];
        }
        i++;
        j++;
    }
    dst[j] = '\0';
}