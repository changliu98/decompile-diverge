#include <stdint.h>

int __cdecl chartorune(unsigned __int16 *rune, const char *str)
{
    uint8_t c  = (uint8_t)str[0];
    uint8_t c1 = (uint8_t)str[1];
    uint8_t c2 = (uint8_t)str[2];

    // 1-byte sequence (ASCII)
    if (c < 0x80)
    {
        *rune = c;
        return 1;
    }

    // Check if the first continuation byte is valid (must start with 10xxxxxx)
    if ((c1 & 0xC0) == 0x80)
    {
        // 2-byte sequence (110xxxxx 10xxxxxx)
        if (c >= 0xC0 && c < 0xE0)
        {
            uint16_t val = ((c & 0x1F) << 6) | (c1 & 0x3F);
            
            // Reject overlong encodings (value must be > 0x7F)
            if (val > 0x7F)
            {
                *rune = val;
                return 2;
            }
        }
        // 3-byte sequence (1110xxxx 10xxxxxx 10xxxxxx)
        else if (c >= 0xE0 && c < 0xF0)
        {
            // Check if the second continuation byte is valid
            if ((c2 & 0xC0) == 0x80)
            {
                uint16_t val = ((c & 0x0F) << 12) | ((c1 & 0x3F) << 6) | (c2 & 0x3F);
                
                // Reject overlong encodings (value must be > 0x7FF)
                if (val > 0x7FF)
                {
                    *rune = val;
                    return 3;
                }
            }
        }
    }

    // Fallback for invalid bytes or invalid sequences
    *rune = 128; // 0x80
    return 1;
}