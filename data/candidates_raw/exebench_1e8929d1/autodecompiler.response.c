void char2hex(char c, char * hex) {
    char high = c >> 4;
    if (high < 10) {
        hex[0] = high + '0';
    } else {
        hex[0] = high - 10 + 'a';
    }

    c &= 0x0f;

    if (c < 10) {
        hex[1] = c + '0';
    } else {
        hex[1] = c - 10 + 'a';
    }
}