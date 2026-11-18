int archive_string_append_from_wcs(struct archive_string *as, const wchar_t *w, size_t len) {
    int ret_val = 0;
    mbstate_t state;
    char *p;
    char *limit;
    size_t remaining = len;

    memset(&state, 0, 8);

    if (archive_string_ensure(as, as->length + len + 1) == NULL) {
        return -1;
    }

    p = as->s + as->length;
    limit = as->s + as->buffer_length - __ctype_get_mb_cur_max() - 1;

    while (*w != L'\0' && remaining > 0) {
        if (p >= limit) {
            as->length = p - as->s;
            as->s[as->length] = '\0';
            
            if (archive_string_ensure(as, as->length + remaining * 2 + 1) == NULL) {
                return -1;
            }
            
            p = as->s + as->length;
            limit = as->s + as->buffer_length - __ctype_get_mb_cur_max() - 1;
        }

        int n = wcrtomb(p, *w, &state);
        w++;

        if (n == -1) {
            if (errno == 84) { // EILSEQ
                *p++ = '?';
                ret_val = -1;
            } else {
                ret_val = -1;
                break;
            }
        } else {
            p += n;
        }

        remaining--;
    }

    as->length = p - as->s;
    as->s[as->length] = '\0';

    return ret_val;
}