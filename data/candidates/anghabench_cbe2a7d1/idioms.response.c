static inline unsigned int REG_A5XX_VPC_SO_BUFFER_OFFSET(unsigned int x, int r)
{
    return (x << r) | (x >> (32 - r));
}