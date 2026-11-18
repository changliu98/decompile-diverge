char revchar(char c) {
    if (c >= 'A' && c <= 'Z') {
        c -= 'A';
    } else if (c >= 'a' && c <= 'z') {
        c = c - 'a' + 26;
    } else if (c >= '0' && c <= '9') {
        c = c - '0' + 52;
    } else if (c == '+') {
        c = '>';
    } else if (c == '/') {
        c = '?';
    }
    return c;
}