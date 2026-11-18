void decipher(unsigned long *v, unsigned long *k)
{
    unsigned long y=v[0];
    unsigned long z=v[1];
    unsigned long sum=0x1328b7bd67ULL;
    unsigned long delta=0x9e3779b9;
    unsigned long n=31;

    while (n-- > 0)
    {
        z -= (((y << 4) ^ (y >> 5)) + y) ^ (sum + k[sum>>11 & 3]);
        sum -= delta;
        y -= (((z << 4) ^ (z >> 5)) + z) ^ (sum + k[sum&3]);
    }

    v[0]=y; v[1]=z;
}