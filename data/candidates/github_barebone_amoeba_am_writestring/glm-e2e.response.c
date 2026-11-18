int am_writestring(struct am_state *ctx, const char *str) {
    write_cb_t write_cb;
    unsigned long len;
    unsigned long space_left;

    write_cb = (write_cb_t)ctx->field_38;

    if (str != NULL) {
        len = strlen(str);
    } else {
        len = 0;
    }

    if (len > 0xFF) {
        return -1;
    }

    if (len < 0x20) {
        // Write length as a single byte (0xA0 + len)
        if (am_writechar(ctx, 0xA0 + len) != 0) {
            return -1;
        }
    } else {
        // Write escape byte 0xD9, then length as a single byte
        if (am_writechar(ctx, 0xD9) != 0) {
            return -1;
        }
        if (am_writechar(ctx, len) != 0) {
            return -1;
        }
    }

    space_left = ctx->write_ptr - &ctx->buffer[0];

    if (space_left + len > 0x1000) {
        // Flush the buffer if the string doesn't fit
        ctx->write_ptr = &ctx->buffer[0];

        if (space_left > 0) {
            ctx->last_error = write_cb(ctx, &ctx->buffer[0], space_left);
            if (ctx->last_error != 0) {
                return -1;
            }
        }

        if (len > 0x1000) {
            // If the string is larger than the buffer, write it directly
            ctx->last_error = write_cb(ctx, str, len);
            return ctx->last_error;
        }
    }

    // Copy the string into the buffer and advance the write pointer
    memcpy(ctx->write_ptr, str, len);
    ctx->write_ptr += len;

    return 0;
}