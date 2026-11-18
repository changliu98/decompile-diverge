void squeeze(uint8_t *s)
{
    uint8_t i;
    uint8_t carry = 0;

    for (i = 0; i < 31; i++)
    {
        s[i] += carry;
        carry = s[i] >> 8;
        s[i] &= 0xff;
    }
    s[31] += carry;
    s[31] &= 127;
    carry = s[31] >> 7;
    s[31] &= 127;

    carry *= 19;
    for (i = 0; i < 31; i++)
    {
        s[i] += carry;
        carry = s[i] >> 8;
        s[i] &= 0xff;
    }
    s[31] += carry;
}