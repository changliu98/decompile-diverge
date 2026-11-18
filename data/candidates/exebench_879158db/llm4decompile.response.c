unsigned long xorshf96(unsigned long *x, unsigned long *y, unsigned long *z)
{
    *x ^= *x << 16;
    *x ^= *x >> 5;
    *x ^= *x << 1;
    t = *x;
    *x = *y;
    *y = *z;
    *z = t ^ *x ^ *y;
    return *z;
}