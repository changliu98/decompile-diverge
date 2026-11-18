void _prtl16(unsigned long num, char *str)
{
    char *digits = "0123456789abcdef";
    char temp[9];
    int i, j;

    temp[0] = '\0';
    for (i = 1; i < 9; i++) {
        temp[i] = digits[num & 0x0f];
        num >>= 4;
    }

    for (i = 8; i > 0; i--) {
        if (temp[i] != '0')
            break;
    }

    if (i == 0)
        i = 1;

    for (j = 0; i >= 0; i--, j++) {
        str[j] = temp[i];
    }
}