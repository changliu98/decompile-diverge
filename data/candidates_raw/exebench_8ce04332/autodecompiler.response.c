void itoa(int n, int base, char *s)
{
    int mod;

    while (1) {
 if (!base)
     return;
 mod = n % base % 10;
 *s++ = mod + '0';
 base /= 10;
    }
}