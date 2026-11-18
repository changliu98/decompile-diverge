int ff_amf_get_string(const unsigned char *data, const unsigned char *data_end,
                      char *key, char *value, int value_size)
{
    int size, key_len, ret;
    double numval;
    long longval;

    key_len = strlen(key);

    for (;;) {
        if (*data == 0x03 || data >= data_end) // AMF_STRING
            break;
        size = ff_amf_tag_size(data, data_end);
        if (size < 0)
            size = data_end - data;
        data += size;
    }

    if (data_end - data < 4)
        return -1;

    data++;

    do {
        unsigned char *p;
        p = (unsigned char *)&size;
        *p++ = *data++;
        *p++ = *data++;
        size = (size << 8) | *p;

        if (!size)
            return -1;

        if (size < 0 || size >= data_end - data)
            return -1;

        data += size;

        if (size == key_len && !memcmp(data - size, key, size)) {
            switch (*data++) {
            case 0x00:
                longval = ((long)(*(data++)) << 56) |
                          ((long)(*(data++)) << 48) |
                          ((long)(*(data++)) << 40) |
                          ((long)(*(data++)) << 32) |
                          (*(data++)) << 24 |
                          (*(data++)) << 16 |
                          (*(data++)) << 8 |
                          (*(data++));
                numval = longval;
                snprintf(value, value_size, "%g", numval);
                break;
            case 0x01:
                snprintf(value, value_size, "%s",
                         *data ? "true" : "false");
                break;
            case 0x02:
                {
                    int len;
                    p = (unsigned char *)&len;
                    *p++ = *data++;
                    *p++ = *data++;
                    len = (len << 8) | *p;

                    if (len + 1 > value_size)
                        len = value_size;
                    av_strlcpy(value, (char *)data, len + 1);
                }
                break;
            default:
                return -1;
            }
            ret = 0;
            goto end;
        } else {
            size = ff_amf_tag_size(data, data_end);
            if (size < 0 || size >= data_end - data)
                return -1;
            data += size;
        }
    } while (1);
end:
    return ret;
}