static size_t defaultPrevCharLen(const char *buf, size_t buf_len, size_t pos, size_t *col_len) {
    (void)(buf); (void)(buf_len); (void)(pos);
    if (col_len != NULL) *col_len = 1;
    return 1;
}