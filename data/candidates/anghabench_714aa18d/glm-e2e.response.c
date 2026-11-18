int is_valid_ref_char(char c) {
    if (c <= ' ') {
        return 0;
    }
    if (c == '*' || c == ':' || c == '?' || (c >= '#' && c <= '$') || c == '^' || c == '~') {
        return 0;
    }
    return 1;
}