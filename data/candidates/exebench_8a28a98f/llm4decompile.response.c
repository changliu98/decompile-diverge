char *itoa(int value, char *str, int base)
{
    static const char *digits = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz";
    char *pstr = str;

    if (base < 2 || base > 36) {
        *pstr = '\0';
        return str;
    }

    do {
        *pstr++ = digits[value % base];
    } while ((value /= base) != 0);

    *pstr-- = '\0';

    do {
        char c = *str;
        *str++ = *pstr;
        *pstr-- = c;
    } while (str > pstr);

    return pstr;
}