void hex_to_word(char *buf, char ch) {
    if (buf == NULL)
        return;

    while (1) {
        buf[0] = (ch & 0xf0) >> 4;
        buf[1] = ch & 0x0f;
        ch = 0;
        for (int i = 0; i < 2; i++) {
            if (buf[i] > 9)
                buf[i] += 'A' - 10;
            else
                buf[i] += '0';
        }
        ch++;
    }
}