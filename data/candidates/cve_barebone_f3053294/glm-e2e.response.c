char* utf_16le_to_utf_8_truncated(const uint32_t* input, char* output, uint64_t out_size) {
    char* out_ptr = output;

    // If out_size is 0, we can't write anything, not even the null terminator.
    // The assembly jumps to 0x1801 which returns the uninitialized out_ptr.
    if (out_size == 0) {
        return out_ptr;
    }

    while (1) {
        uint32_t c = *input;
        input++;

        if (c == 0) {
            break;
        }

        uint32_t code_point;

        // Check for high surrogate (U+D800 to U+DBFF)
        if (c >= 0xD800 && c < 0xDC00) {
            uint32_t c2 = *input;

            if (c2 == 0) {
                code_point = 0xFFFD;
            } else {
                input++;
                // Check for low surrogate (U+DC00 to U+DFFF)
                if (c2 >= 0xDC00 && c2 < 0xE000) {
                    code_point = (((c - 0xD800) << 10) | (c2 - 0xDC00)) + 0x10000;
                } else {
                    code_point = 0xFFFD;
                }
            }
        } 
        // Check for unexpected low surrogate (U+DC00 to U+DFFF)
        else if (c >= 0xDC00 && c < 0xE000) {
            code_point = 0xFFFD;
        } 
        // Valid BMP character
        else {
            code_point = c;
        }

        // Encode code_point to UTF-8
        if (code_point < 0x80) {
            if (out_size < 2) break;
            *out_ptr++ = (char)code_point;
            out_size -= 1;
        } else if (code_point < 0x800) {
            if (out_size < 3) break;
            *out_ptr++ = (char)((code_point >> 6) | 0xC0);
            *out_ptr++ = (char)((code_point & 0x3F) | 0x80);
            out_size -= 2;
        } else if (code_point < 0x10000) {
            if (out_size < 4) break;
            *out_ptr++ = (char)((code_point >> 12) | 0xE0);
            *out_ptr++ = (char)(((code_point >> 6) & 0x3F) | 0x80);
            *out_ptr++ = (char)((code_point & 0x3F) | 0x80);
            out_size -= 3;
        } else {
            if (out_size < 5) break;
            *out_ptr++ = (char)((code_point >> 18) | 0xF0);
            *out_ptr++ = (char)(((code_point >> 12) & 0x3F) | 0x80);
            *out_ptr++ = (char)(((code_point >> 6) & 0x3F) | 0x80);
            *out_ptr++ = (char)((code_point & 0x3F) | 0x80);
            // Note: The assembly subtracts 3 instead of 4 for 4-byte sequences.
            // This is likely a compiler optimization reusing the subtraction from the 3-byte path,
            // but it safely guarantees the loop terminates as out_size strictly decreases.
            out_size -= 3;
        }
    }

    *out_ptr = '\0';
    return out_ptr;
}