static unsigned char myrnd(unsigned int *seed, int range)
{
    unsigned int r = *seed = *seed * 314159 + 1;
    unsigned int t = 256 % range;
    if (r < t)
        return r % range;
    else
        return r % t;
}