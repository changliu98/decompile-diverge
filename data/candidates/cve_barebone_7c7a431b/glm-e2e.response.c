void RemoveICCProfileFromResourceBlock(void *str_info) {
    size_t length = GetStringInfoLength(str_info);
    if (length < 16) {
        return;
    }

    unsigned char *datum = GetStringInfoDatum(str_info);
    unsigned char *p = datum;

    while (1) {
        if (p < datum || p > datum + length - 16) {
            break;
        }

        unsigned char *start = p;

        if (LocaleNCompare((const char *)p, "8BIM", 4) != 0) {
            break;
        }

        unsigned int resource_size;
        unsigned short resource_id;
        unsigned short pascal_string_size;

        p = PushLongPixel(2, p, &resource_size);
        p = PushShortPixel(2, p, &resource_id);
        p = PushShortPixel(2, p, &pascal_string_size);
        p = PushLongPixel(2, p, &resource_size);

        if (resource_id == 0x040f) {
            size_t block_size = ((resource_size + 1) & ~1UL) + 12;
            unsigned char *dest = start + block_size;
            size_t offset = start - datum;
            size_t copy_size = length - block_size - offset;
            
            CopyMagickMemory(start, dest, copy_size);
            SetStringInfoLength(str_info, length - block_size);
            break;
        } else {
            p += resource_size;
            if (resource_size & 1) {
                p += 1;
            }
        }
    }
}