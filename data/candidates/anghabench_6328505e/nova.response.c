int is_uletter(char c) {
    char r;
    r = ((c >= 'A') && (c <= 'Z'));
    return r & 0x01;
}