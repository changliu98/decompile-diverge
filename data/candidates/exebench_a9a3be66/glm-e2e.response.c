char* byte2bits(int8_t b, char *out) {
    for (int i = 7; i >= 0; i--) {
        *out++ = ((b >> i) & 1) + '0';
    }
    *out = '\0';
    return out;
}