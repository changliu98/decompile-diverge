int escape(const char **src, int flag, size_t *out_len) {
    const char *p = *src;
    char *out_start = (char *)*src; // -0x28(%rbp) holds the initial output pointer
    char *out = out_start;
    char c = *p;

    while (c != '\0') {
        if (c == '\\') {
            p++;
            char next = *(p);
            switch (next) {
                case '\\':
                    *out++ = '\\';
                    *out = '\0';
                    *out_len = out - out_start;
                    return 0;
                case 'a':
                    *out = '\a';
                    break;
                case 'b':
                    *out = '\b';
                    break;
                case 'e':
                    if (flag == 0) {
                        *out = '\0';
                        *out_len = out - out_start;
                        return 1;
                    }
                    *out = 'c';
                    break;
                case 'f':
                    *out = '\f';
                    break;
                case 'n':
                    *out = '\n';
                    break;
                case 'r':
                    *out = '\r';
                    break;
                case 't':
                    *out = '\t';
                    break;
                case 'v':
                    *out = '\v';
                    break;
                case '0': case '1': case '2': case '3':
                case '4': case '5': case '6': case '7':
                    {
                        int max_digits = 3;
                        if (flag == 0 && next == '0') {
                            max_digits = 4;
                        }
                        int val = 0;
                        int digits = max_digits;
                        while (digits > 0) {
                            if (*p >= '0' && *p <= '7') {
                                val = (val << 3) + (*p - '0');
                                p++;
                                digits--;
                            } else {
                                break;
                            }
                        }
                        p--;
                        if (flag != 0 && val == 0x25) {
                            *out++ = '%';
                            *out = '%';
                        } else {
                            *out = (char)val;
                        }
                    }
                    break;
                default:
                    *out = next;
                    break;
            }
        } else {
            *out = c;
        }
        p++;
        out++;
        c = *p;
    }

    *out = '\0';
    *out_len = out - out_start;
    return 0;
}