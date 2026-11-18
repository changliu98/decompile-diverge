int utoa(char *str, unsigned int val, int spec)
{
    char *pt;
    char *pt2;
    char tmp[128];
    char hexupper[] = "0123456789ABCDEF";
    char hexlower[] = "0123456789abcdef";
    char *hex;
    int base;

    switch(spec)
    {
        case 'i':
        case 'd':
        case 'u':
            base = 10;
            break;
        case 'o':
            base = 8;
            break;
        case 'X':
            base = 16;
            hex = hexupper;
            break;
        case 'x':
            base = 16;
            hex = hexlower;
            break;
        default:
            return -1;
    }

    pt2 = str;
    pt = tmp + 127;

    do {
        if (base == 8) {
            *pt-- = '0' + (val & 0x7);
        }
        else if (base == 10) {
            *pt-- = '0' + (val % 10);
        }
        else if (base == 16) {
            *pt-- = hex[val & 0xf];
        }
        val /= base;
    } while (val);

    while (++pt < tmp + 128) {
        *pt2++ = *pt;
    }

    *pt2 = '\0';

    return pt2 - str;
}