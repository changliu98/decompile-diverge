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

    if (bytecnt)
        wpc->file_format = *byteptr++;

    if (--bytecnt)
        wpc->config.qmode = (wpc->config.qmode & ~0xff) | *byteptr++;

    if (--bytecnt)
        wpc->channel_layout = *byteptr++ << 16;

    if (--bytecnt)
        wpc->channel_layout += *byteptr++ << 8;

    if (--bytecnt)
        wpc->channel_layout += *byteptr++;

    if (bytecnt) {
        if (bytecnt < (reorder_size = *byteptr++))
            return 0;

        bytecnt -= reorder_size;

        if (!(wpc->channel_reordering = malloc ((size_t) reorder_size)))
            return 1;

        while (reorder_size--) {
            if (bytecnt)
                wpc->channel_reordering [wpc->config.num_channels - reorder_size - 1] = *byteptr++;
            else
                wpc->channel_reordering [wpc->config.num_channels - reorder_size - 1] = (unsigned char) (wpc->config.num_channels - reorder_size - 1);

            --bytecnt;
        }
    }

    return 1;
}