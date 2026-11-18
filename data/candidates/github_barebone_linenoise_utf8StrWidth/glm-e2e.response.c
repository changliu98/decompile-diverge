size_t utf8StrWidth(const char *s, size_t len) {
    size_t width = 0;
    size_t i = 0;
    int prev_was_combining = 0;

    while (i < len) {
        int c;
        size_t char_len = utf8NextCharLen(s + i, &c);

        // If the character is an ANSI escape sequence (0x1b)
        if (c == 0x1b) {
            size_t esc_len = ansiEscapeLen(s + i, len - i);
            if (esc_len > 0) {
                i += esc_len;
                continue;
            }
        }

        // Handle combining marks
        if (prev_was_combining) {
            prev_was_combining = 0;
        } else {
            width += utf8CharWidth(c);
        }

        // Check if the current character is a combining mark for the next iteration
        if (isCombiningMark(c)) {
            prev_was_combining = 1;
        }

        i += char_len;
    }

    return width;
}