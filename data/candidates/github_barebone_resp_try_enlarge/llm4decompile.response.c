int try_enlarge(RespResponse *r, uint32_t add_size) {
    uint32_t new_size = r->buf_size;
    while (new_size < r->used_size + add_size)
        new_size *= 2;

    char *new_buf = realloc(r->buf, new_size);
    if (new_buf == NULL)
        return -1;

    r->buf = new_buf;
    r->buf_size = new_size;

    return 0;
}