int read_int_delta(const uint8_t *data, int32_t *val, int32_t *prev_val) {
    int bytes_read;

    // Byte 0
    *val = data[0] & 0x7F;
    if (data[0] < 0x80) {
        *prev_val += *val;
        *val = *prev_val;
        bytes_read = 1;
        return bytes_read;
    }

    // Byte 1
    *val |= (data[1] & 0x7F) << 7;
    if (data[1] < 0x80) {
        *prev_val += *val;
        *val = *prev_val;
        bytes_read = 2;
        return bytes_read;
    }

    // Byte 2
    *val |= (data[2] & 0x7F) << 14;
    if (data[2] < 0x80) {
        *prev_val += *val;
        *val = *prev_val;
        bytes_read = 3;
        return bytes_read;
    }

    // Byte 3
    *val |= (data[3] & 0x7F) << 21;
    if (data[3] < 0x80) {
        *prev_val += *val;
        *val = *prev_val;
        bytes_read = 4;
        return bytes_read;
    }

    // Byte 4
    *val |= (data[4] & 0x7F) << 28;
    
    // Final delta addition and assignment
    *prev_val += *val;
    *val = *prev_val;
    bytes_read = 5;

    return bytes_read;
}