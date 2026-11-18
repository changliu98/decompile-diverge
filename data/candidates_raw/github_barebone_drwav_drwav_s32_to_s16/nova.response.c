static void func0(unsigned short *dest, const int *src, const size_t len)
{
    size_t i;

    for (i = 0; i < len; i++) {
        unsigned int val = (unsigned int)src[i];
        unsigned short val16 = (unsigned short)(val >> 16);

        dest[i] = val16;
    }
}