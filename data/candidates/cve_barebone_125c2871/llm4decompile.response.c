int ff_amf_get_field_value(uint8_t *data, uint8_t *data_end,
                           const char *name, uint8_t *dst, int dst_size)
{
    int namelen = strlen(name);
    int size;

    while (*data != 3 && data < data_end) {
        size = ff_amf_tag_size(data, data_end);
        if (size < 0)
            size = data_end - data;
        data += size;
    }

    if (data_end - data < 3)
        return -1;
    data++;

    while (1) {
        size = (data[0] << 8) | data[1];
        if (!size)
            break;
        if (data_end - (data + 2) < size)
            return -1;
        data += 2 + size;

        if (size == namelen && !memcmp(data - size, name, namelen)) {
            switch (*(data - size - 1)) {
            case 0:
                snprintf(dst, dst_size, "%g",
                         (double)(*(uint64_t*)(data - size - 1 - 8)));
                return 0;
            case 1:
                snprintf(dst, dst_size, "%s", *(data - size - 1) ? "true" : "false");
                return 0;
            case 2:
                av_strlcpy(dst, data - size,
                           ((size + 1) < (dst_size) ? (size + 1) : (dst_size)));
                return 0;
            }
            return -1;
        }

        size = ff_amf_tag_size(data, data_end);
        if (size < 0 || data_end - data <= size)
            return -1;
        data += size;
    }

    return -1;
}