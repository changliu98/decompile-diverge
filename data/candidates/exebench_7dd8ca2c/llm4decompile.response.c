void hex_to_word(char *two_chars, unsigned char hex)
{
    char i;

    if (two_chars == NULL)
        return;

    two_chars[0] = (hex & 0xF0) >> 4;
    two_chars[1] = (hex & 0x0F);

    for (i = 0; i < 2; i++) {
        if (two_chars[i] > 9)
            two_chars[i] += 'A' - 10;
        else
            two_chars[i] += '0';
    }
}