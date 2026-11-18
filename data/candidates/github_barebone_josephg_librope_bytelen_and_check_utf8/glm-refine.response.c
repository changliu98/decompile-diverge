ssize_t bytelen_and_check_utf8(const uint8_t *str)
{
    const uint8_t *p = str;

    while (*p)
    {
        size_t cp_size = codepoint_size(*p);
        
        // If the leading byte is invalid, return an error
        if (cp_size == (size_t)-1)
            return -1;

        // Check the continuation bytes (size - 1 bytes following the leading byte)
        for (size_t i = 1; i < cp_size; ++i)
        {
            // A valid UTF-8 continuation byte must match the bit pattern 10xxxxxx (0x80)
            if ((p[i] & 0xC0) != 0x80)
                return -1;
        }

        p += cp_size;
    }

    return p - str;
}