long vcolon(const char *str, long end, long i) {
    if (i == end) {
        return -(i + 1);
    }

    if (str[i] == ':') {
        return i + 1;
    }

    while (i < end) {
        char c = str[i];
        
        // Check if c is '\t' (0x09), '\r' (0x0D), or ' ' (0x20)
        if (c == '\t' || c == '\r' || c == ' ') {
            i++;
        } else if (c == ':') {
            return i + 1;
        } else {
            return -(i + 1);
        }
    }

    return -(i + 1);
}