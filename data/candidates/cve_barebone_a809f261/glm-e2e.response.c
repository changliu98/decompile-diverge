int skip_boxes(int *pos, const uint8_t *buf, int buf_size) {
    GetByteContext gbc;
    int header_size = 4;

    if (*pos > buf_size) {
        return 0xacb9aabe; // Error/Invalid state code
    }

    buf += *pos;
    buf_size -= *pos;
    bytestream2_init(&gbc, buf, buf_size);

    while (1) {
        if (bytestream2_peek_le16(&gbc) == 0xaff) {
            return 0; // Success
        }

        if (bytestream2_peek_le64(&gbc) == 0x204c584a0c000000ULL) {
            return 0; // Success
        }

        if (bytestream2_get_bytes_left(&gbc) < 8) {
            return 0xacb9aabe; // Error: Not enough bytes
        }

        uint64_t size = bytestream2_get_be32(&gbc);

        if (size == 1) {
            if (bytestream2_get_bytes_left(&gbc) < 12) {
                return 0xacb9aabe; // Error: Not enough bytes for extended size
            }
            size = bytestream2_get_be64(&gbc);
            header_size = 12;
        }

        if (size == 0) {
            return 0xbebbb1b7; // Error: Invalid box size
        }

        if (size <= (uint64_t)header_size + 4) {
            return 0xbebbb1b7; // Error: Box size too small
        }

        *pos += size;
        bytestream2_skip(&gbc, (uint32_t)(size - header_size));

        if (bytestream2_get_bytes_left(&gbc) <= 0) {
            return 0xacb9aabe; // Error: No more bytes left
        }
    }
}