static int read_file_dentry_set(struct vlc_memstream *ms,
                                  struct vlc_memstream **p_ms, int *pi_size)
{
    struct vlc_memstream *ms_tmp = NULL;
    bool b_is_header = false;
    int i_size;

    for (i_size = 0; ; i_size++)
    {
        uint8_t *p_data;
        int i_data;

        if (vlc_memstream_get(ms, &p_data, &i_data))
            goto error;

        if (p_data[0]!= 0x81)
        {
            msg_Warn(vlc_memstream_get_logger(ms),
                     "invalid header byte (0x%02x)", p_data[0]);
            i_size = -2;
            break;
        }

        if (p_data[1] < 3)
        {
            *pi_size = p_data[1] + 1;
            continue;
        }

        if (vlc_memstream_get(ms, &p_data, &i_data))
            goto error;

        if (p_data[0]!= 0x81)
        {
            i_size = p_data[1] + 1;
            continue;
        }

        if (p_data[1] < 3)
        {
            *pi_size = p_data[1] + 1;
            continue;
        }

        ms_tmp = vlc_memstream_new(p_data, i_data);
        if (ms_tmp == NULL)
            goto error;

        if (b_is_header)
        {
            vlc_memstream_put(ms_tmp, 0);
            b_is_header = false;
        }

        *pi_size = i_size + 1;
        *p_ms = ms_tmp;
        i_size = 0;
        break;
    }

    if (b_is_header)
    {
        vlc_memstream_