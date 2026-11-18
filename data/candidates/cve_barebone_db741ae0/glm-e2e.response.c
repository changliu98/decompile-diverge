int burl_normalize_2F_to_slash_fix(buffer *b, int start, int pos) {
    char *ps = b->ptr;
    int blen = buffer_string_length(b);
    int end = (start < 0) ? blen : start;
    int i = pos;
    int j = pos;

    while (pos < end) {
        ps[j] = ps[pos];
        
        if (ps[pos] == '%' && ps[pos + 1] == '2' && ps[pos + 2] == 'F') {
            ps[j] = '/';
            pos += 2;
        }
        
        pos++;
        j++;
    }

    if (start >= 0) {
        memmove(ps + j, ps + start, blen - start);
        j += blen - start;
    }

    buffer_string_set_length(b, j);
    
    return start;
}