int cbs_av1_read_uvlc(CodedBitstreamContext *ctx, GetBitContext *gbc,
                             const char *name, uint32_t *write_to,
                             uint32_t range_min, uint32_t range_max)
{
    uint32_t value;
    int bit_count = 0;
    int bit_offset;
    int bit_position;
    char bitstring[64];

    if (ctx->trace_enable)
        bit_position = get_bits_count(gbc);

    while (bit_count + 1 <= get_bits_left(gbc)) {
        if (get_bits1(gbc))
            break;
        bitstring[bit_count++] = '0';
    }
    if (bit_count + 1 > get_bits_left(gbc)) {
        av_log(ctx->log_ctx, 16, "Invalid uvlc code at %s: bitstream ended.\n", name);
        return -(0x4E494E49);
    }
    bitstring[bit_count++] = '1';

    if (bit_count < 32) {
        value = get_bits_long(gbc, bit_count - 1);
        for (bit_offset = 0; bit_offset < bit_count - 1; bit_offset++)
            bitstring[bit_count + bit_offset] = (value >> ((bit_count - 1) - bit_offset)) & 1 ? '1' : '0';
        value += (1 << (bit_count - 1)) - 1;
    } else {
        value = 0xFFFFFFFF;
    }

    if (ctx->trace_enable) {
        bitstring[bit_count] = '\0';
        ff_cbs_trace_syntax_element(ctx, bit_position, name, NULL, bitstring, value);
    }

    if (value < range_min || value > range_max) {
        av_log(ctx->log_ctx, 16, "%s out of range: %u, but must be in [%u,%u].\n",
               name, value, range_min, range_max);
        return -(0x4E494E49);
    }

    *write_to = value;
    return 0;
}