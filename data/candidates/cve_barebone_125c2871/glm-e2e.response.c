int ff_amf_get_field_value(const uint8_t *data, const uint8_t *end, const char *name, char *buf, int buf_size) {
    int name_len = strlen(name);
    int tag_size;
    int str_len;
    uint8_t type;
    uint64_t num_val;

    // Skip over AMF elements until we find an AMF Object (type 0x03)
    while (1) {
        if (*data != 0x03 || data >= end) {
            break;
        }
        tag_size = ff_amf_tag_size(data, end);
        if (tag_size < 0) {
            tag_size = end - data;
        }
        data += tag_size;
    }

    // Check if there are enough bytes left for the object end marker (3 bytes)
    if (end - data < 3) {
        return -1;
    }

    // Skip the 0x03 marker
    data++;

    // Iterate through the object's properties
    while (1) {
        const uint8_t **p_data = &data;
        
        // Read the 2-byte big-endian string length for the key
        *p_data += 2;
        str_len = ((*p_data)[-2] << 8) | (*p_data)[-1];

        // A key length of 0 indicates the end of the object
        if (str_len == 0) {
            return -1;
        }

        // Boundary check
        if (str_len < 0 || str_len >= end - data) {
            return -1;
        }

        // Advance data pointer past the key string
        data += str_len;

        // Check if the current key matches the requested name
        if (str_len == name_len && memcmp(data - str_len, name, name_len) == 0) {
            // Key matched; read the value type
            type = *data++;

            switch (type) {
                case 0x00: // AMF Number (8 bytes, big-endian double)
                    num_val = ((uint64_t)data[0] << 56) |
                              ((uint64_t)data[1] << 48) |
                              ((uint64_t)data[2] << 40) |
                              ((uint64_t)data[3] << 32) |
                              ((uint64_t)data[4] << 24) |
                              ((uint64_t)data[5] << 16) |
                              ((uint64_t)data[6] << 8)  |
                              ((uint64_t)data[7]);
                    snprintf(buf, buf_size, "%g", *(double *)&num_val);
                    return 0;

                case 0x01: // AMF Boolean (1 byte)
                    snprintf(buf, buf_size, "%s", *data ? "true" : "false");
                    return 0;

                case 0x02: // AMF String (2-byte length header + string data)
                    str_len = (data[0] << 8) | data[1];
                    data += 2;
                    av_strlcpy(buf, (const char *)data, (str_len + 1 <= buf_size) ? (str_len + 1) : buf_size);
                    return 0;

                default: // Unsupported AMF type for value
                    return -1;
            }
        } else {
            // Key did not match; skip the value
            tag_size = ff_amf_tag_size(data, end);
            if (tag_size < 0 || tag_size >= end - data) {
                return -1;
            }
            data += tag_size;
        }
    }
}