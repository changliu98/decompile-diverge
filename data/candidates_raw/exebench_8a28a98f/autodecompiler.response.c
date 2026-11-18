char *itoa(int value, char *string, int radix)
{



    char tmp[33];
    char *tp = tmp;
    int i;
    char *sp;

    if (radix > 36 || radix <= 1) {
        *string = '\0';
        return string;
    }

    sp = string;

    do {
        *tp++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + value % radix];
        value /= radix;
    } while (value);

    *tp-- = '\0';

    while (tp > tmp) {
        i = *tmp;
        *tmp++ = *tp;
        *tp-- = i;
    }

    return sp;

}