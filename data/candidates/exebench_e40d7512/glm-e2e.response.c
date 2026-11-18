char* scnline(int val, char *str, int bit) {
    int i = 8;
    while (--i != 0) {
        val <<= 1;
        char c = (val & 0x80) ? (char)bit : ' ';
        *str++ = c;
    }
    return str;
}