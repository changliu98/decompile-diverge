static void mix_16h_to_32_s2(int *dest, short *src, int n)
{
    n >>= 1;
    while (n--) {
        *dest++ += (*src++ >> 1);
        *dest++ += (*src++ >> 1);
        src += 6;
    }
}