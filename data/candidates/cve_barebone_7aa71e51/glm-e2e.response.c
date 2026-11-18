void *smb_fdata(void *out, const char *buf, const char *fmt, const char *endbuf, int depth) {
    char local_fmt[128];
    char *ret_val;
    char *next_fmt;
    const char *ret_ptr;
    const char *new_buf;
    const char *close_bracket;
    long remaining_len;

    if (*fmt == '\0') {
        if (smb_fdata_depth == 0 && buf < endbuf) {
            remaining_len = endbuf - buf;
            (*(void (**)(void *, const char *, ...))out)(out, "%s\n", remaining_len);
            smb_print_data(out, buf, (int)remaining_len);
            return (void *)(buf + remaining_len);
        }
        return (void *)buf;
    }

    switch (*fmt) {
        case '#':
            fmt++;
            ret_ptr = buf;
            break;
            
        case '%':
            fmt++;
            buf = endbuf;
            break;
            
        case '*':
            fmt++;
            while (buf < endbuf) {
                smb_fdata_depth++;
                new_buf = (const char *)smb_fdata(out, buf, fmt, endbuf, depth);
                smb_fdata_depth--;
                
                if (new_buf == NULL) {
                    return NULL;
                }
                if (new_buf == buf) {
                    return (void *)buf;
                }
                buf = new_buf;
            }
            break;
            
        case '|':
            fmt++;
            if (buf >= endbuf) {
                return (void *)buf;
            }
            break;
            
        case '[':
            fmt++;
            if (buf >= endbuf) {
                return (void *)buf;
            }
            
            memset(local_fmt, 0, 128);
            close_bracket = strchr(fmt, ']');
            if (close_bracket == NULL || (close_bracket - fmt + 1) > 128) {
                return (void *)buf;
            }
            
            strncpy(local_fmt, fmt, close_bracket - fmt);
            local_fmt[close_bracket - fmt] = '\0';
            fmt = close_bracket + 1;
            
            buf = (const char *)smb_fdata1(out, buf, local_fmt, endbuf, depth);
            if (buf == NULL) {
                return NULL;
            }
            break;
            
        default:
            (*(void (**)(void *, const char *, ...))out)(out, "%c", *fmt);
            fmt++;
            break;
    }

    return (void *)buf;
}