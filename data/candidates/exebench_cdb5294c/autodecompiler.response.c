void int2str(int n, int base, char *s)
{
    int mod;
    char *p = s;

    while (1) {
 if (base) {
     mod = n % base;
     *s++ = mod < 10 ? mod + '0' : mod + 'a' - 10;
     n /= base;
 } else
     break;
    }
    *s = '\0';
}