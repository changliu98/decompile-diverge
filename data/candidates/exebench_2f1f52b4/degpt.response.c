int isLegalUTF8(uchar *byte_sequence, int sequence_length)
{
    // Validate that the length is within the allowed range for UTF-8 sequences (1 to 4 bytes)
    if (sequence_length < 1 || sequence_length > 4) {
        return 0;
    }

    // Handle 1-byte ASCII characters
    if (sequence_length == 1) {
        // Valid ASCII range (0x00-0x7F) or start of multi-byte sequences (0xC2-0xF4)
        // Note: 0xC0 and 0xC1 are invalid as they would lead to overlong encodings
        return (*byte_sequence >= 0x00 && *byte_sequence <= 0x7F) || (*byte_sequence >= 0xC2 && *byte_sequence <= 0xF4);
    }

    // Handle 2-byte sequences
    if (sequence_length == 2) {
        // The continuation byte must be in the range 0x80-0xBF
        if (byte_sequence[1] < 0x80 || byte_sequence[1] > 0xBF) {
            return 0;
        }
        // The first byte must be >= 0xC2 to avoid overlong encodings (0xC0, 0xC1 are invalid)
        if (byte_sequence[0] < 0xC2) {
            return 0;
        }
        // Prevent overlong encoding for U+0000 to U+007F: 0xE0 0x80-0x9F is invalid
        if (byte_sequence[0] == 0xE0 && byte_sequence[1] < 0xA0) {
            return 0;
        }
        // Prevent overlong encoding for U+0000 to U+07FF: 0xF0 0x80-0x8F is invalid
        if (byte_sequence[0] == 0xF0 && byte_sequence[1] < 0x90) {
            return 0;
        }
        // Prevent encoding of surrogate halves (U+D800 to U+DFFF): 0xF4 0x90-0xBF is invalid
        if (byte_sequence[0] == 0xF4 && byte_sequence[1] > 0x8F) {
            return 0;
        }
        return 1;
    }

    // Handle 3-byte sequences
    if (sequence_length == 3) {
        // The second continuation byte must be in the range 0x80-0xBF
        if (byte_sequence[2] < 0x80 || byte_sequence[2] > 0xBF) {
            return 0;
        }
        // The first continuation byte must be in the range 0x80-0xBF
        if (byte_sequence[1] < 0x80 || byte_sequence[1] > 0xBF) {
            return 0;
        }
        // The first byte must be >= 0xE0 for 3-byte sequences
        if (byte_sequence[0] < 0xE0) {
            return 0;
        }
        // Prevent overlong encoding for U+0000 to U+07FF: 0xE0 0x80-0x9F is invalid
        if (byte_sequence[0] == 0xE0 && byte_sequence[1] < 0xA0) {
            return 0;
        }
        // Prevent overlong encoding for U+0000 to U+07FF: 0xF0 0x80-0x8F is invalid
        if (byte_sequence[0] == 0xF0 && byte_sequence[1] < 0x90) {
            return 0;
        }
        // Prevent encoding of surrogate halves (U+D800 to U+DFFF): 0xF4 0x90-0xBF is invalid
        if (byte_sequence[0] == 0xF4 && byte_sequence[1] > 0x8F) {
            return 0;
        }
        return 1;
    }

    // Handle 4-byte sequences
    if (sequence_length == 4) {
        // The third continuation byte must be in the range 0x80-0xBF
        if (byte_sequence[3] < 0x80 || byte_sequence[3] > 0xBF) {
            return 0;
        }
        // The second continuation byte must be in the range 0x80-0xBF
        if (byte_sequence[2] < 0x80 || byte_sequence[2] > 0xBF) {
            return 0;
        }
        // The first continuation byte must be in the range 0x80-0xBF
        if (byte_sequence[1] < 0x80 || byte_sequence[1] > 0xBF) {
            return 0;
        }
        // The first byte must be >= 0xF0 for 4-byte sequences
        if (byte_sequence[0] < 0xF0) {
            return 0;
        }
        // Prevent overlong encoding for U+0000 to U+FFFF: 0xF0 0x80-0x8F is invalid
        if (byte_sequence[0] == 0xF0 && byte_sequence[1] < 0x90) {
            return 0;
        }
        // Prevent encoding of code points above U+10FFFF: 0xF4 0x90-0xBF is invalid
        if (byte_sequence[0] == 0xF4 && byte_sequence[1] > 0x8F) {
            return 0;
        }
        return 1;
    }

    // Default return for any other cases (should not be reached due to earlier checks)
    return 0;
}