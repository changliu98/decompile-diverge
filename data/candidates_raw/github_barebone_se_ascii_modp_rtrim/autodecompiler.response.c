size_t modp_rtrim(char* str, size_t len)
{
    char c;
    for (;;) {
        if (len == 0) {
            return 0;
        }
        c = str[len-1];
        switch(c) {
        case ' ': case '\n': case '\t': case '\r':
            str[len-1] = '\0';
            len--;
            break;
        default:
            return len;
        }
    }
}