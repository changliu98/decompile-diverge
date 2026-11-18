int cbc_get_uvlc(void *ctx, void *gbc, char *name, void *write_to, unsigned int range_min, unsigned int range_max)
{
    struct CodedBitstreamContext *cs = (CodedBitstreamContext *)ctx;
    struct GetBitContext *gb = (GetBitContext *)gbc;
    char bits[-1];
    int i; int j;
    unsigned int value;
    int zeroes;
    int trace_pos;
    if (cs->trace_enable)
        trace_pos = cbc_get_bitstream_position(gb);
    for (i = 0, zeroes = 0; get_bit(gb); i++, zeroes++)
        bits[i] = '0';
    bits[i++] = '1';
    if (zeroes >= 32)
        value = (4294967295U);
    else {
        value = get_be_uif(gb, zeroes);
        for (j = 0; j < zeroes; j++)
            bits[i++] = (value & (1 << (zeroes - j - 1))) ? '1' : '0';
        value += (1 << zeroes) - 1;
    }
    if (cs->trace_enable) {
        bits[i] = '\0';
        cbc_log_bitstream(cs, trace_pos, name, ((void *)0), bits, value);
    }
    if (value < range_min || value > range_max) {
        range_max = (range_max);
        log_print(cs->log_ctx, 16, "%s out of range: %u, but must be in [%u,%u].\n", name, value, range_min, range_max);
        return -12345;
    }
    *(unsigned int *)write_to = value;
    return 0;
}