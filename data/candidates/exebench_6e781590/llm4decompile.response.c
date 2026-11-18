void replace_char(char *buf, char from, char to) {
    char *ch;

    ch = buf;
    while (*ch != 0) {
        if (*ch == from)
            *ch = to;
        ch++;
    }
}