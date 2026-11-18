void ltox(unsigned long value, char *str)
{
    int i;
    char *tab = "0123456789ABCDEF";

    for (i = 0; i < 8; i++) {
 str[9 - i] = tab[(value & 0xF)];
 value >>= 4;
    }
    str[0] = '0';
    str[1] = 'x';
    str[10] = '\n';
    str[11] = 0;
}