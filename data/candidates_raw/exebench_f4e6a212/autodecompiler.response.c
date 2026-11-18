static void add_short_to_int(int *dest, short *src, int n)
{
    n >>= 1;
    while (n--) {
        *dest++ += (*src++ >> 1);
        *dest++ += (*src++ >> 1);
        src += 6;
    }
}