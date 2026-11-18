void mobi_buffer_move(Buffer *buf, int offset, size_t len) {
    size_t abs_offset = abs(offset);
    unsigned char *target = buf->data + buf->cur_offset;

    if (offset >= 0) {
        if (buf->cur_offset + abs_offset + len > buf->maxlen) {
            buf->error = 9;
            return;
        }
        target += abs_offset;
    } else {
        if (buf->cur_offset < abs_offset) {
            buf->error = 9;
            return;
        }
        target -= abs_offset;
    }

    memmove(target, buf->data + buf->cur_offset, len);
    buf->cur_offset += len;
}