static int func0(char *buf, int buf_size) {
    int i = 0;
    int found_dot = 0;
    char *p = buf;

    if (buf_size < 1 || buf == NULL)
        return 0;

    if (buf_size < 4) {
        buf[buf_size] = '\0';
        return 1;
    }

    for (i = buf_size - 3; i >= 0; i--) {
        if (*p!= 0)
            found_dot = (i!= 0);
        if (found_dot) {
            if (*p & 0x80)
                *(p + 1) = '.';
            else
                *(p + 1) = *p & 0x7f;
        }
        p++;
    }

    *p = '\0';
    p--;
    *p = '.';
    p--;
    *p = '.';
    p--;

    if (found_dot) {
        if (*p & 0x80)
            *p = '.';
    }

    return found_dot;
}