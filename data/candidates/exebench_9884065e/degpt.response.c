/*
 * Decodes a single UTF-8 character from the input string 'in'.
 *
 * Parameters:
 *   in  - Pointer to the current position in the UTF-8 encoded string.
 *   chr - Pointer to an integer where the decoded Unicode code point will be stored.
 *
 * Returns:
 *   Pointer to the next byte in the string after the decoded character.
 *
 * Logic:
 *   Checks the leading byte to determine the number of bytes in the UTF-8 sequence
 *   (1 to 6 bytes). Validates that continuation bytes have the correct format (10xxxxxx).
 *   Combines the significant bits from each byte to reconstruct the Unicode code point.
 *   Handles ASCII (1-byte) as a fallback.
 */
char * _PL__utf8_get_char(char *input_ptr, int *code_point_ptr)
{
    // 2-byte UTF-8 sequence: 110xxxxx 10xxxxxx
    // Mask 0xe0 (11100000) checks the first byte starts with 110.
    // Mask 0xc0 (11000000) checks the second byte starts with 10.
    if ((((int)*input_ptr & 0xe0U) == 0xc0) && (((int)input_ptr[1] & 0xc0U) == 0x80)) {
        // Extract 5 bits from first byte and 6 bits from second byte.
        // Combine them to form the 11-bit Unicode code point.
        *code_point_ptr = ((int)*input_ptr & 0x1fU) << 6 | (int)input_ptr[1] & 0x3fU;
        return input_ptr + 2;
    }
    // 3-byte UTF-8 sequence: 1110xxxx 10xxxxxx 10xxxxxx
    // Mask 0xf0 (11110000) checks the first byte starts with 1110.
    else if ((((int)*input_ptr & 0xf0U) == 0xe0) &&
            ((((int)input_ptr[1] & 0xc0U) == 0x80 && (((int)input_ptr[2] & 0xc0U) == 0x80)))) {
        // Extract 4 bits from first, 6 from second, 6 from third.
        // Combine to form the 16-bit Unicode code point.
        *code_point_ptr = ((int)*input_ptr & 0xfU) << 0xc | ((int)input_ptr[1] & 0x3fU) << 6 | (int)input_ptr[2] & 0x3fU;
        return input_ptr + 3;
    }
    // 4-byte UTF-8 sequence: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
    // Mask 0xf8 (11111000) checks the first byte starts with 11110.
    else if ((((int)*input_ptr & 0xf8U) == 0xf0) &&
            (((((int)input_ptr[1] & 0xc0U) == 0x80 && (((int)input_ptr[2] & 0xc0U) == 0x80)) &&
             (((int)input_ptr[3] & 0xc0U) == 0x80)))) {
        // Extract 3 bits from first, 6 from next three.
        // Combine to form the 21-bit Unicode code point.
        *code_point_ptr = ((int)*input_ptr & 7U) << 0x12 | ((int)input_ptr[1] & 0x3fU) << 0xc | ((int)input_ptr[2] & 0x3fU) << 6 |
               (int)input_ptr[3] & 0x3fU;
        return input_ptr + 4;
    }
    // 5-byte UTF-8 sequence: 111110xx 10xxxxxx ...
    // Mask 0xfc (11111100) checks the first byte starts with 111110.
    else if (((((int)*input_ptr & 0xfcU) == 0xf8) && (((int)input_ptr[1] & 0xc0U) == 0x80)) &&
            ((((int)input_ptr[2] & 0xc0U) == 0x80 &&
             ((((int)input_ptr[3] & 0xc0U) == 0x80 && (((int)input_ptr[4] & 0xc0U) == 0x80)))))) {
        // Extract 2 bits from first, 6 from next four.
        // Combine to form the 26-bit Unicode code point.
        *code_point_ptr = ((int)*input_ptr & 3U) << 0x18 | ((int)input_ptr[1] & 0x3fU) << 0x12 | ((int)input_ptr[2] & 0x3fU) << 0xc |
               ((int)input_ptr[3] & 0x3fU) << 6 | (int)input_ptr[4] & 0x3fU;
        return input_ptr + 5;
    }
    // 6-byte UTF-8 sequence: 1111110x 10xxxxxx ...
    // Mask 0xfe (11111110) checks the first byte starts with 1111110.
    else if ((((int)*input_ptr & 0xfeU) == 0xfc) &&
            ((((((int)input_ptr[1] & 0xc0U) == 0x80 && (((int)input_ptr[2] & 0xc0U) == 0x80)) &&
              (((int)input_ptr[3] & 0xc0U) == 0x80)) &&
             ((((int)input_ptr[4] & 0xc0U) == 0x80 && (((int)input_ptr[5] & 0xc0U) == 0x80)))))) {
        // Extract 1 bit from first, 6 from next five.
        // Combine to form the 31-bit Unicode code point.
        *code_point_ptr = ((int)*input_ptr & 1U) << 0x1e | ((int)input_ptr[1] & 0x3fU) << 0x18 | ((int)input_ptr[2] & 0x3fU) << 0x12 |
               ((int)input_ptr[3] & 0x3fU) << 0xc | ((int)input_ptr[4] & 0x3fU) << 6 | (int)input_ptr[5] & 0x3fU;
        return input_ptr + 6;
    }
    // ASCII character (1-byte): 0xxxxxxx
    // Fallback for single-byte characters.
    else {
        *code_point_ptr = (uint)(byte)*input_ptr;
        return input_ptr + 1;
    }
}