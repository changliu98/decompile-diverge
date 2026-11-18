void mobi_buffer_move(MOBIBuffer *buf, int offset, size_t len) {
    size_t abs_offset = abs(offset);
    if (offset < 0) {
        if (buf->offset < abs_offset) {
            buf->error = MOBI_BUFFER_END;
            return;
        }
        abs_offset *= -1;
    } else {
        if (buf->offset + abs_offset + len > buf->maxlen) {
            buf->error = MOBI_BUFFER_END;
            return;
        }
    }
    memmove(buf->data + buf->offset, buf->data + buf->offset + abs_offset, len);
    buf->offset += len;
}