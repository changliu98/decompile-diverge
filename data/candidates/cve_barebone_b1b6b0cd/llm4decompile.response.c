int read_new_config_info (WavpackContext *wpc, WavpackMetadata *wpmd)
{
    int bytecnt = wpmd->byte_length;
    unsigned char *byteptr = wpmd->data;
    int reorder_size;

    wpc->version_five = 1;
    wpc->channel_layout = 0;
    wpc->config.qmode = 0;
    wpc->file_format = 0;

    if (wpc->channel_reordering) {
        free (wpc->channel_reordering);
        wpc->channel_reordering = NULL;
    }

    if (bytecnt) {
        wpc->file_format = *byteptr++;
        --bytecnt;
    }

    if (bytecnt) {
        wpc->config.qmode &= ~0xff;
        wpc->config.qmode |= *byteptr++;
        --bytecnt;
    }

    if (bytecnt) {
        wpc->channel_layout = *byteptr++ << 16;
        --bytecnt;
    }

    if (bytecnt) {
        wpc->channel_layout += *byteptr++ << 8;
        --bytecnt;
    }

    if (bytecnt) {
        wpc->channel_layout += *byteptr++;
        --bytecnt;
    }

    if (bytecnt) {
        reorder_size = *byteptr++;
        --bytecnt;

        if (bytecnt < reorder_size)
            return 0;

        wpc->channel_reordering = malloc ((size_t) reorder_size);

        if (wpc->channel_reordering) {
            int ch;

            for (ch = 0; ch < reorder_size; ++ch) {
                if (bytecnt)
                    wpc->channel_reordering [ch] = *byteptr++;
                else
                    wpc->channel_reordering [ch] = ch;
                --bytecnt;
            }
        }
    }

    return 1;
}