char *parse_fmt(char *fmt, int *type, int *size)
{
    char *start = fmt;

    while (*fmt && *fmt != '%')
        fmt++;

    if (*fmt == '%') {
        fmt++;

        if (*fmt == '%') {
            *size = fmt - start + 1;
            *type = -1;
            fmt++;
        } else if (*fmt == 'v') {
            *type = 15;
            *size = fmt - start;
            fmt++;
        }
    }

    if (!*fmt) {
        *type = -1;
        *size = fmt - start;
    }

    return fmt;
}