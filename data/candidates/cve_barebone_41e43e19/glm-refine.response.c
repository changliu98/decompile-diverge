int __cdecl read_new_config_info(WavpackContext *wpc, WavpackMetadata *wpmd)
{
    int bytecnt = wpmd->byte_length;
    unsigned __int8 *byteptr = (unsigned __int8 *)wpmd->data;
    int i;
    int nchans;

    wpc->version_five = 1;
    wpc->channel_layout = 0;
    wpc->config.qmode = 0;
    wpc->file_format = 0;

    if (wpc->channel_reordering)
    {
        free(wpc->channel_reordering);
        wpc->channel_reordering = NULL;
    }

    if (!bytecnt)
        return 1;

    // Byte 0: File format
    wpc->file_format = *byteptr++;

    // Byte 1: QMode (lower 8 bits)
    wpc->config.qmode = *byteptr++;
    bytecnt -= 2;

    if (!bytecnt)
        return 1;

    // Byte 2: Channel layout (high 8 bits of 24-bit layout)
    wpc->channel_layout = *byteptr++ << 16;
    bytecnt -= 1;

    if (!bytecnt)
    {
        wpc->channel_layout += wpc->config.num_channels;
        return 1;
    }

    // Byte 3: Number of channels (low 8 bits of 24-bit layout)
    nchans = *byteptr++;
    wpc->channel_layout += nchans;
    bytecnt -= 1;

    if (!bytecnt)
        return 1;

    // Remaining bytes: Channel reordering mapping
    if (bytecnt <= nchans)
    {
        wpc->channel_reordering = (unsigned __int8 *)malloc(nchans);
        if (wpc->channel_reordering)
        {
            for (i = 0; i < nchans; ++i)
            {
                if (bytecnt)
                {
                    wpc->channel_reordering[i] = *byteptr++;
                    bytecnt--;
                }
                else
                {
                    wpc->channel_reordering[i] = i;
                }
            }
        }
        return 1;
    }

    return 0;
}