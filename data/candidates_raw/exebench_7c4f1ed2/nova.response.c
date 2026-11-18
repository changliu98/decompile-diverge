static inline void func0(short num, unsigned char *buf, int *length)
{
    *length = 2;
    buf[0] = (num      ) & 0xff;
    buf[1] = (num >>  8) & 0xff;
}