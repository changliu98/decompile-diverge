static unsigned char linear2ulaw(short sample)
{
    short s = sample;
    int sign = (s >> 8) & 0x80;
    int exp;
    if (sign)
        s = -s;
    s += BIAS;
    exp = linear2ulaw_exp_lut[s >> 7];
    return (unsigned char)(~((s >> (exp + 3)) & 0xf | (exp << 4) | sign));
}