void encipher(unsigned long *v, unsigned long *k)
{
    unsigned long y=v[0];
    unsigned long z=v[1];
    unsigned long sum=0;
    unsigned long delta=0x9e3779b9;
    unsigned long n=32;

    while (n-- > 0) {
        y += (z << 4 ^ z >> 5) + z + sum + k[sum & 3];
        sum += delta;
        z += (y << 4 ^ y >> 5) + y + sum + k[(sum>>11) & 3];
    }

    v[0]=y; v[1]=z;
}