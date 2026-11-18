/*
 * Decodes a single UTF-8 character from the input string.
 *
 * Parameters:
 *   utf8char - Pointer to the start of the UTF-8 encoded character.
 *   size     - The remaining number of bytes available in the buffer.
 *   charlen  - Pointer to store the number of bytes consumed by the character.
 *
 * Returns:
 *   The decoded Unicode code point on success.
 *   0xffffffff on error (invalid sequence, insufficient data, or null terminator).
 */
uint utf8_decode_v2(char *input_ptr, size_t buffer_len, size_t *out_byte_count)
{
    /* Check for empty buffer or null terminator */
    if ((buffer_len == 0) || (*input_ptr == '\0')) {
        if (out_byte_count) *out_byte_count = 0;
        return 0xffffffff;
    }
    /* Handle 1-byte ASCII character (0xxxxxxx) */
    else if (((int)*input_ptr & 0x80U) == 0) {
        if (out_byte_count) *out_byte_count = 1;
        return (int)*input_ptr & 0x7f;
    }
    /* Handle 2-byte character (110xxxxx 10xxxxxx) */
    else if (((int)*input_ptr & 0xe0U) == 0xc0) {
        if (out_byte_count) *out_byte_count = 2;
        /* Ensure there are enough bytes and the continuation byte is valid */
        if ((buffer_len < 2) || (input_ptr[1] == '\0')) {
            return 0xffffffff;
        }
        return ((int)*input_ptr & 0x1fU) << 6 | (int)input_ptr[1] & 0x3fU;
    }
    /* Handle 3-byte character (1110xxxx 10xxxxxx 10xxxxxx) */
    else if (((int)*input_ptr & 0xf0U) == 0xe0) {
        if (out_byte_count) *out_byte_count = 3;
        /* Ensure there are enough bytes and all continuation bytes are valid */
        if (((buffer_len < 3) || (input_ptr[1] == '\0')) || (input_ptr[2] == '\0')) {
            return 0xffffffff;
        }
        return ((int)*input_ptr & 0xfU) << 0xc | ((int)input_ptr[1] & 0x3fU) << 6 | (int)input_ptr[2] & 0x3fU;
    }
    /* Handle 4-byte character (11110xxx 10xxxxxx 10xxxxxx 10xxxxxx) */
    else if (((int)*input_ptr & 0xf8U) == 0xf0) {
        if (out_byte_count) *out_byte_count = 4;
        /* Ensure there are enough bytes and all continuation bytes are valid */
        if ((((buffer_len < 4) || (input_ptr[1] == '\0')) || (input_ptr[2] == '\0')) || (input_ptr[3] == '\0')) {
            return 0xffffffff;
        }
        return ((int)*input_ptr & 7U) << 0xf | ((int)input_ptr[1] & 0x3fU) << 0xc | ((int)input_ptr[2] & 0x3fU) << 6 | (int)input_ptr[3] & 0x3fU;
    }
    /* Invalid UTF-8 sequence */
    else {
        if (out_byte_count) *out_byte_count = 0;
        return 0xffffffff;
    }
}