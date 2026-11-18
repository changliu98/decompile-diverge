int unicoder_utf32_decode(uint *output_code_point, uchar *input_buffer, uint byte_order)
{
    // Validate endianness parameter: must be 1 (big-endian) or 2 (little-endian)
    if (byte_order != 1 && byte_order != 2) {
        return -4;
    }
    // Validate input pointers to prevent null pointer dereference
    if (input_buffer == NULL || output_code_point == NULL) {
        return -1;
    }

    uint code_point_value = 0;
    // Iterate over 4 bytes to decode a UTF-32 character
    for (int i = 0; i < 4; i++) {
        if (byte_order == 2) {
            // Little-endian: shift existing bits left and add new byte at the least significant position
            if (i > 0) {
                code_point_value <<= 8;
            }
            code_point_value |= input_buffer[i];
        } else {
            // Big-endian: shift existing bits right and add new byte at the most significant position
            if (i > 0) {
                code_point_value >>= 8;
            }
            code_point_value |= ((uint)input_buffer[i]) << 24;
        }
    }

    // Check for invalid Unicode code points: above the maximum valid value (0x10FFFF)
    if (code_point_value >= 0x110000) {
        return -0x10;
    }
    // Check for surrogate pairs, which are invalid in UTF-32
    if (code_point_value >= 0xd800 && code_point_value <= 0xdfff) {
        return -0x10;
    }

    // Store the decoded Unicode code point in the result pointer
    *output_code_point = code_point_value;
    // Return the number of bytes consumed (4 bytes for UTF-32)
    return 4;
}