static int
mustache_buffer_insert(MUSTACHE_BUFFER* buf, off_t off, const void* data, size_t n)
{
    if(buf->n + n > buf->alloc) {
        size_t new_alloc = (buf->n + n) * 2;
        uint8_t* new_data;

        new_data = (uint8_t*) realloc(buf->data, new_alloc);
        if(new_data == NULL)
            return -1;

        buf->data = new_data;
        buf->alloc = new_alloc;
    }

    if(off < buf->n)
        memmove(buf->data + off + n, buf->data + off, buf->n - off);

    memcpy(buf->data + off, data, n);
    buf->n += n;
    return 0;
}