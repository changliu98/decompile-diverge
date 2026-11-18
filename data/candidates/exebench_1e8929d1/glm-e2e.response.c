void convert2ASCII(char val, char *out) {
    char high = val >> 4;
    if (high < 10) {
        out[0] = high + '0';
    } else {
        out[0] = high - 10 + 'a';
    }

    char low = val & 0xF;
    if (low < 10) {
        out[1] = low + '0';
    } else {
        out[1] = low - 10 + 'a';
    }
}