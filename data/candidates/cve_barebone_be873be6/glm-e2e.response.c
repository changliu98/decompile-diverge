void msg_puts_printf(char *str, int maxlen) {
    char *p;
    char *s = NULL;
    char *tofree = NULL;
    char *p_start = str;

    for (p = str; ; p++) {
        if (maxlen >= 0 && (p - str) >= maxlen) {
            break;
        }
        if (*p == '\0') {
            break;
        }

        if (!silent_mode || p_verbose != NULL) {
            if (*p == '\n') {
                int len = p - p_start;
                s = alloc(len + 3);
                if (s != NULL) {
                    memcpy(s, p_start, len);
                    if (!info_message) {
                        s[len++] = '\r';
                    }
                    s[len++] = '\n';
                    s[len] = '\0';
                    if (info_message) {
                        mch_msg(s);
                    } else {
                        mch_errmsg(s);
                    }
                    vim_free(s);
                }
                p_start = p + 1;
            }
        }

        if (*p == '\r' || *p == '\n') {
            msg_col = 0;
        } else {
            msg_col++;
        }
    }

    if (*p_start != '\0' && (!silent_mode || p_verbose != NULL)) {
        if (maxlen > 0 && strlen(p_start) > maxlen) {
            tofree = vim_strnsave(p_start, maxlen);
            p_start = tofree;
        }
        if (p_start != NULL) {
            if (info_message) {
                mch_msg(p_start);
            } else {
                mch_errmsg(p_start);
            }
            vim_free(tofree);
        }
    }

    msg_didout = 1;
}