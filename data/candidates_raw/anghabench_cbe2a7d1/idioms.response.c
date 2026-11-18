static inline unsigned int rotl32(unsigned int x, int r)
{
    return (x << r) | (x >> (32 - r));
}