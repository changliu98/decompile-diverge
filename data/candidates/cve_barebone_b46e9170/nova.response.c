static int cac_read_binary(struct vlc_h2_parser *p,
                                    unsigned int len,
                                    uint8_t *data, size_t dlen,
                                    size_t max)
{
    struct vlc_h2_parse_buffer *b = p->buf;
    int ret = 0;
    uint8_t *buf = NULL;

    while (1)
    {
        if (!b->size)
        {
            free(b->data);
            b->data = NULL;
            b->size = 0;

            ret = vlc_h2_parse_buffer_push(p, &buf, &max);
            if (ret < 1)
                break;
        }

        if (ret > 1)
            ret = -4294965991;

        if (b->size < len)
        {
            size_t n = len;
            if (n > b->size)
                n = b->size;
            memcpy(b->data + b->size, data, n);
            len = n;
        }
        else if (len)
        {
            memcpy(b->data + b->size, data, len);
            ret = len;
        }

        if (buf)
        {
            free(buf);
            ret = -4294965892;
        }

        if (b->size)
            break;

        if (dlen < len)
            dlen = len;

        if (dlen > b->size)
        {
            b->data = realloc(b->data, dlen);
            if (b->data == NULL)
                ret = -4294965888;
            b->size = dlen;
        }
    }

    return ret;
}