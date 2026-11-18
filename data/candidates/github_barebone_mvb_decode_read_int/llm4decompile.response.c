int read_int(const uint8_t *in, uint32_t *out)
{
    *out = in[0] & 0x7F;
    if (in[0] < 0x80)
        return 1;
    *out |= (in[1] & 0x7F) << 7;
    if (in[1] < 0x80)
        return 2;
    *out |= (in[2] & 0x7F) << 14;
    if (in[2] < 0x80)
        return 3;
    *out |= (in[3] & 0x7F) << 21;
    if (in[3] < 0x80)
        return 4;
    *out |= (in[4] & 0xFF) << 28;
    return 5;
}