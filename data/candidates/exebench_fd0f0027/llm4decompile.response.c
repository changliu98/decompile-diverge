void ltostr(unsigned int value, char *str)
{
    int i;
    str[0] = '\0';
    str[8] = '\0';
    for (i = 0; i < 8; i++) {
        str[7 - i] = (value & 0xF) + '0';
        if (str[7 - i] > '9')
            str[7 - i] = str[7 - i] - '0' + 'A' - 10;
        value = value >> 4;
    }
}