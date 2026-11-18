void func0(char *str, char ch) {
    if (str == NULL)
        return;

    str[0] = (ch & 0xC0) >> 6;
    str[1] = (ch & 0x3F) >> 3;
    str[2] = (ch & 0x07);
    str[3] = '\0';

    for (int i = 0; i < 3; i++) {
        if (str[i] < 4) {
            str[i] += 48;
        }
    }
}