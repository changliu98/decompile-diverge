const char *parse_fmt(const char *fmt, int *type, ptrdiff_t *len) {
    const char *start = fmt;
    
    while (*fmt != '\0' && *fmt != '%') {
        fmt++;
    }
    
    if (*fmt == '%') {
        char next = fmt[1];
        if (next == '%') {
            *len = fmt - start + 1;
            *type = -1;
            return fmt + 2;
        } else if (next == 'v') {
            *type = 15;
            *len = fmt - start;
            return fmt + 2;
        }
    }
    
    // Falls through here if it's not a valid format specifier (or end of string)
    *type = -1;
    *len = fmt - start;
    return fmt;
}