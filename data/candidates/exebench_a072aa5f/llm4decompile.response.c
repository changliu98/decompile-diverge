void decrypt (unsigned long *v, unsigned long *k)
{
    unsigned long y=v[0];
    unsigned long z=v[1];
    unsigned long sum=0xC6EF3720;
    unsigned long delta=0x9E3779B9;
    unsigned long n=32;

    while (n-- > 0)
    {
        z -= (((y << 4) + k[2]) ^ (y + sum) ^ ((y >> 5) + k[3]));
        y -= (((z << 4) + k[0]) ^ (z + sum) ^ ((z >> 5) + k[1]));
        sum -= delta;
    }

    v[0]=y;
    v[1]=z;
}