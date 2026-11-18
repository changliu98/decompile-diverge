int mustache_buffer_insert(struct buffer *buf, size_t pos, const void *src, size_t len) {
    if (buf->length + len > buf->capacity) {
        size_t new_capacity = (buf->length + len) * 2;
        char *new_data = realloc(buf->data, new_capacity);
        if (!new_data) {
            return -1;
        }
        buf->data = new_data;
        buf->capacity = new_capacity;
    }

    if (pos < buf->length) {
        memmove(buf->data + pos + len, buf->data + pos, buf->length - pos);
    }

    memcpy(buf->data + pos, src, len);
    buf->length += len;

    return 0;
}