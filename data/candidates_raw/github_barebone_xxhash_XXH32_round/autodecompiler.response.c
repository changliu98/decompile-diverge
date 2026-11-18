unsigned int hash_combine(unsigned int h1, unsigned int h2)
{
    h1 += 0x9e3779b9 * h2;
    h1 = (h1 << 13) | (h1 >> 19);
    h1 *= 0x9e3779b1;
    return h1;
}