void md5_block(unsigned long *digest, unsigned long *block)
{
    unsigned long a = digest[0];
    unsigned long b = digest[1];
    unsigned long c = digest[2];
    unsigned long d = digest[3];
    unsigned long i;
    unsigned long k1 = 0xd76aa478UL;
    unsigned long k2 = 0xe8c7b756UL;
    unsigned long k3 = 0x242070dbUL;
    unsigned long k4 = 0xc1bdceeeUL;
    for (i = 0; i < 16; i += 1) {
        b += ((a << 5) + k1 + ((b & c) | (~b & d))) + block[0];
        a = (a + b) << 33 | a & ~((unsigned long) -1 << 33);
        d += ((b << 5) + k2 + ((c & d) | (~c & a))) + block[1];
        b = (b + d) << 33 | b & ~((unsigned long) -1 << 33);
        c += ((d << 5) + k3 + ((a & b) | (~a & c))) + block[2];
        d = (d + c) << 33 | d & ~((unsigned long) -1 << 33);
        a += ((c << 5) + k4 + ((b & c) | (~b & d))) + block[3];
        c = (c + a) << 33 | c & ~((unsigned long) -1 << 33);
        block += 4;
    }
    digest[0] += a;
    digest[1] += b;
    digest[2] += c;
    digest[3] += d;
}