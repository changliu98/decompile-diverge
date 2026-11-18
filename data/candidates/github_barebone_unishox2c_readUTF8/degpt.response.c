int32_t readUTF8(char *input_buffer, int buffer_length, int current_index, int *decoded_length)
{
    int32_t decoded_codepoint = 0;

    // Check for 2-byte UTF-8 sequence: 110xxxxx 10xxxxxx
    if (current_index < buffer_length - 1 && ((int)input_buffer[current_index] & 0xe0U) == 0xc0 && ((int)input_buffer[current_index + 1] & 0xc0U) == 0x80) {
        *decoded_length = 2;
        // Combine the 5 bits from the first byte and 6 bits from the second byte
        decoded_codepoint = ((int)input_buffer[current_index + 1] & 0x3fU) + ((int)input_buffer[current_index] & 0x1fU) * 0x40;
        // Reject overlong encodings: values below 0x80 should be encoded in 1 byte
        if ((uint)decoded_codepoint < 0x80) {
            decoded_codepoint = 0;
        }
    } else if (current_index < buffer_length - 2 && ((int)input_buffer[current_index] & 0xf0U) == 0xe0 &&
               ((int)input_buffer[current_index + 1] & 0xc0U) == 0x80 && ((int)input_buffer[current_index + 2] & 0xc0U) == 0x80) {
        // Check for 3-byte UTF-8 sequence: 1110xxxx 10xxxxxx 10xxxxxx
        *decoded_length = 3;
        // Combine the 4 bits from the first byte and 6 bits from the next two bytes
        decoded_codepoint = ((int)input_buffer[current_index + 2] & 0x3fU) + (((int)input_buffer[current_index + 1] & 0x3fU) + ((int)input_buffer[current_index] & 0xfU) * 0x40) * 0x40;
        // Reject overlong encodings: values below 0x800 should be encoded in 2 bytes
        if ((uint)decoded_codepoint < 0x800) {
            decoded_codepoint = 0;
        }
    } else if (current_index < buffer_length - 3 && ((int)input_buffer[current_index] & 0xf8U) == 0xf0 &&
               ((int)input_buffer[current_index + 1] & 0xc0U) == 0x80 &&
               ((int)input_buffer[current_index + 2] & 0xc0U) == 0x80 && ((int)input_buffer[current_index + 3] & 0xc0U) == 0x80) {
        // Check for 4-byte UTF-8 sequence: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
        *decoded_length = 4;
        // Combine the 3 bits from the first byte and 6 bits from the next three bytes
        decoded_codepoint = ((int)input_buffer[current_index + 3] & 0x3fU) +
              (((int)input_buffer[current_index + 2] & 0x3fU) + (((int)input_buffer[current_index + 1] & 0x3fU) + ((int)input_buffer[current_index] & 7U) * 0x40) * 0x40)
              * 0x40;
        // Reject overlong encodings: values below 0x10000 should be encoded in 3 bytes
        if ((uint)decoded_codepoint < 0x10000) {
            decoded_codepoint = 0;
        }
    }
    return decoded_codepoint;
}