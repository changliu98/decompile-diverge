void MD5Transform(unsigned int buf[4], unsigned int const in[16])
{
    register unsigned int a, b, c, d;

    a = buf[0];
    b = buf[1];
    c = buf[2];
    d = buf[3];

    (a += (d ^ (b & (c ^ d))) + in[0] + 0xd76aa478, a = a << 7 | a >> 25, a += b);
    (d += (c ^ (a & (b ^ c))) + in[1] + 0xe8c7b756, d = d << 12 | d >> 20, d += a);
    (c += (b ^ (d & (a ^ b))) + in[2] + 0x242070db, c = c << 17 | c >> 15, c += d);
    (b += (a ^ (c & (d ^ a))) + in[3] + 0xc1bdceee, b = b << 22 | b >> 10, b += c);