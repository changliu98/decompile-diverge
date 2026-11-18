int iwgif_read_image(struct iwgif_state *r) {
    int ret = 0;
    struct lzw_state lzw; // Allocates 0x6040 bytes on the stack
    uint8_t block_size;

    if (!iwgif_read(r, r->read_buf, 9)) {
        return 0;
    }

    r->left = iw_get_ui16le(r->read_buf);
    r->top = iw_get_ui16le(r->read_buf + 2);
    r->width = iw_get_ui16le(r->read_buf + 4);
    r->height = iw_get_ui16le(r->read_buf + 6);

    r->interlace = (r->packed_fields >> 6) & 1;
    int has_local_color_table = (r->packed_fields >> 7) & 1;

    if (has_local_color_table) {
        r->num_colors = 1 << ((r->packed_fields & 7) + 1);
        if (!iwgif_read_color_table(r, &r->num_colors)) {
            return 0;
        }
    }

    if (r->has_transparency) {
        r->palette[r->transparent_index * 4] = 0;
    }

    if (!iwgif_read(r, r->read_buf, 1)) {
        return 0;
    }

    uint8_t min_code_size = r->read_buf[0];
    if (min_code_size < 2 || min_code_size > 11) {
        iw_set_error(r->error_ctx, "Invalid minimum code size");
        return 0;
    }

    if (!iwgif_init_screen(r)) {
        return 0;
    }

    r->total_pixels = (int64_t)r->width * r->height;
    if (!iwgif_make_row_pointers(r)) {
        return 0;
    }

    lzw_init(&lzw, min_code_size);
    lzw_clear(&lzw);

    while (1) {
        if (!iwgif_read(r, r->read_buf, 1)) {
            return 0;
        }

        block_size = r->read_buf[0];
        if (block_size == 0) {
            break;
        }

        if (!iwgif_read(r, r->read_buf, block_size)) {
            return 0;
        }

        if (!lzw_process_bytes(r, &lzw, r->read_buf, block_size)) {
            return 0;
        }

        if (lzw.done) {
            break;
        }

        if (r->image_data >= r->image_data + r->total_pixels) {
            break;
        }
    }

    ret = 1;
    return ret;
}