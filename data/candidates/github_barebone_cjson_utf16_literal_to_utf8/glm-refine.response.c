uint8_t utf16_literal_to_utf8(
    const uint8_t *const input_pointer,
    const uint8_t *const input_end,
    uint8_t **output_pointer)
{
    uint32_t first_code;
    uint32_t second_code;
    uint64_t codepoint;
    uint8_t  utf8_length;
    uint8_t  first_byte_mark;
    uint8_t  utf8_position;
    uint8_t  sequence_length;

    first_byte_mark = 0;

    // A UTF-16 escape sequence is at least 6 characters long (e.g., "\uXXXX")
    if (input_end - input_pointer < 6)
        return 0;

    // Parse the first 4 hex digits after "\u"
    first_code = parse_hex4(input_pointer + 2);

    // High surrogates (0xDC00 - 0xDFFF) are invalid as the first sequence
    if (first_code >= 0xDC00 && first_code <= 0xDFFF)
        return 0;

    if (first_code < 0xD800 || first_code > 0xDBFF)
    {
        // Valid Basic Multilingual Plane (BMP) character
        sequence_length = 6;
        codepoint = first_code;
    }
    else
    {
        // High surrogate detected (0xD800 - 0xDBFF). 
        // It must be followed by a low surrogate "\uXXXX" (12 chars total)
        sequence_length = 12;
        
        if (input_end - (input_pointer + 6) < 6)
            return 0;
        
        // Check for the trailing "\u"
        if (input_pointer[6] != '\\' || input_pointer[7] != 'u')
            return 0;

        second_code = parse_hex4(input_pointer + 8);

        // The second code must be a low surrogate (0xDC00 - 0xDFFF)
        if (second_code < 0xDC00 || second_code > 0xDFFF)
            return 0;

        // Combine high and low surrogates into a single 21-bit codepoint
        codepoint = 0x10000 + (((first_code & 0x3FF) << 10) | (second_code & 0x3FF));
    }

    // Determine UTF-8 encoding length and the bitmask for the leading byte
    if (codepoint < 0x80)
    {
        utf8_length = 1;
        // first_byte_mark remains 0
    }
    else if (codepoint < 0x800)
    {
        utf8_length = 2;
        first_byte_mark = 0xC0; // 110xxxxx
    }
    else if (codepoint < 0x10000)
    {
        utf8_length = 3;
        first_byte_mark = 0xE0; // 1110xxxx
    }
    else if (codepoint <= 0x10FFFF)
    {
        utf8_length = 4;
        first_byte_mark = 0xF0; // 11110xxx
    }
    else
    {
        // Codepoint out of valid Unicode range
        return 0;
    }

    // Encode continuation bytes (right to left)
    for (utf8_position = utf8_length - 1; utf8_position > 0; --utf8_position)
    {
        (*output_pointer)[utf8_position] = (codepoint & 0x3F) | 0x80; // 10xxxxxx
        codepoint >>= 6;
    }

    // Encode the leading byte
    if (utf8_length == 1)
    {
        **output_pointer = codepoint & 0x7F; // 0xxxxxxx
    }
    else
    {
        **output_pointer = first_byte_mark | codepoint;
    }

    // Advance the output pointer
    *output_pointer += utf8_length;

    return sequence_length;
}