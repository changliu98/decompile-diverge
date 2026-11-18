size_t StrSafeCopy(char *dst, const char *src, size_t size) {
    char *p_dst = dst;
    const char *p_src = src;
    size_t remaining = size;

    if (remaining != 0) {
        remaining--; // Reserve space for the null terminator
        if (remaining != 0) {
            do {
                char c = *p_src++;
                *p_dst++ = c;
                if (c == '\0') {
                    break;
                }
                remaining--;
            } while (remaining != 0);
        }
    }

    if (remaining == 0) {
        if (size != 0) {
            *p_dst = '\0'; // Ensure null termination
        }
        // Advance p_src to the end of the source string
        while (*p_src != '\0') {
            p_src++;
        }
    }

    // Return the number of characters copied (excluding the null terminator)
    return (size_t)(p_src - src - 1);
}