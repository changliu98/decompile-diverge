int read_int_delta(const uint8_t *in, uint32_t *out, uint32_t *prev)
{
    *out = in[0] & 0x7F;
    if (in[0] < 0x80) {
        *prev += *out;
        *out = *prev;
        return 1;
    }
    *out |= (in[1] & 0x7F) << 7;
    if (in[1] < 0x80) {
        *prev += *out;
        *out = *prev;
        return 2;
    }
    *out |= (in[2] & 0x7F) << 14;
    if (in[2] < 0x80) {
        *prev += *out;
        *out = *prev;
        return 3;
    }
    *out |= (in[3] & 0x7F) << 21;
    if (in[3] < 0x80) {
        *prev += *out;
        *out = *prev;
        return 4;
    }
    *out |= (in[4] & 0x7F) << 28;
    *prev += *out;
    *out = *prev;
    return 5;
}