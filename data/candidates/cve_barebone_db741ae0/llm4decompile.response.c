int burl_normalize_2F_to_slash_fix(buffer * const b, int qs, int i) {
    char * const p = b->ptr;
    const int blen = buffer_string_length(b);
    int j = i;
    if (qs < 0) qs = blen;
    for (; i < qs; ++i) {
        p[j++] = p[i];
        if (p[i] == '%' && p[i+1] == '2' && p[i+2] == 'F') {
            p[j-1] = '/';
            i += 2;
        }
    }
    if (qs < blen) {
        memmove(p+j, p+qs, (size_t)(blen-qs));
        j += blen - qs;
    }
    buffer_string_set_length(b, (size_t)j);
    return qs;
}