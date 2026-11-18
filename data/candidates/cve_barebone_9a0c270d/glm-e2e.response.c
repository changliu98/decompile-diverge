void trunc_string(char *s, char *buf, int room, int buflen) {
    int len = room - 3;
    long long width = 0;
    int i = 0;
    int e;
    int cells;
    int l;

    if (*s == '\0') {
        if (buflen > 0) {
            *buf = '\0';
        }
        return;
    }

    if (room < 3) {
        len = 0;
    }

    int half = len / 2;

    while (width < half && i < buflen) {
        if (s[i] == '\0') {
            buf[i] = '\0';
            return;
        }

        cells = ptr2cells(&s[i]);
        if (width + cells > half) {
            break;
        }

        width += cells;
        buf[i] = s[i];

        if (has_mbyte) {
            l = mb_ptr2len(&s[i]) - 1;
            while (l > 0) {
                i++;
                if (i == buflen) {
                    break;
                }
                buf[i] = s[i];
                l--;
            }
        }
        i++;
    }

    e = i;

    if (enc_dbcs) {
        cells = vim_strsize(&s[e]);
        while (width + cells > len) {
            cells -= ptr2cells(&s[e]);
            e += mb_ptr2len(&s[e]);
            cells = vim_strsize(&s[e]);
        }
    } else if (enc_utf8) {
        e = strlen(s);
        half = e;

        do {
            half = half - 1 - utf_head_off(s, s + half - 1);
        } while (half > 0 && utf_iscomposing(utf_ptr2char(s + half)));

        cells = ptr2cells(s + half);
        while (width + cells <= len && half != 0) {
            width += cells;
            e = half;
            half = e;
            cells = ptr2cells(s + half);
        }
    } else {
        e = strlen(s);
        while (e - 1 >= 0 && width + ptr2cells(&s[e - 1]) <= len) {
            width += ptr2cells(&s[e - 1]);
            e--;
        }
    }

    if (e <= i + 3) {
        if (s != buf) {
            long long n = strlen(s);
            if (n >= buflen) {
                n = buflen - 1;
            }
            n = n - i + 1;
            if (n < 1) {
                buf[i - 1] = '\0';
            } else {
                memmove(buf + i, s + i, n);
            }
        }
    } else {
        if (i + 3 < buflen) {
            buf[i] = '.';
            buf[i + 1] = '.';
            buf[i + 2] = '.';
            
            long long n = strlen(&s[e]) + 1;
            if (n >= buflen - i - 3) {
                n = buflen - i - 3 - 1;
            }
            memmove(buf + i + 3, &s[e], n);
            buf[i + 3 + n - 1] = '\0';
        } else {
            buf[i - 1] = '\0';
        }
    }
}