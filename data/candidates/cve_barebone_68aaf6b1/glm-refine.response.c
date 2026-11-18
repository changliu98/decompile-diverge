int __cdecl cbs_av1_read_uvlc(
        CodedBitstreamContext *ctx,
        GetBitContext *gbc,
        const char *name,
        uint32_t *write_to,
        uint32_t range_min,
        uint32_t range_max)
{
    char bits[65];
    int i = 0;
    int zeroes = 0;
    uint32_t value;
    int position = 0;

    if (ctx->trace_enable)
        position = get_bits_count(gbc);

    // Read leading zeroes
    for (zeroes = 0; ; ++zeroes)
    {
        if (get_bits_left(gbc) < zeroes + 1)
        {
            av_log(ctx->log_ctx, AV_LOG_ERROR, "Invalid uvlc code at %s: bitstream ended.\n", name);
            return CBS_BAD_VALUE;
        }

        if (get_bits1(gbc))
            break;

        bits[i++] = '0';
    }

    // Read the '1' bit that terminated the loop
    bits[i++] = '1';

    if (zeroes < 32)
    {
        value = get_bits_long(gbc, zeroes);
        
        // Append the read bits to the trace string
        for (int j = 0; j < zeroes; ++j)
        {
            if ((value >> (zeroes - j - 1)) & 1)
                bits[i++] = '1';
            else
                bits[i++] = '0';
        }
        
        // Map to unsigned integer value
        value += (1U << zeroes) - 1;
    }
    else
    {
        // If zeroes >= 32, it exceeds the maximum allowable range for 32-bit unsigned UVLC
        value = 0xFFFFFFFF;
    }

    if (ctx->trace_enable)
    {
        bits[i] = '\0';
        ff_cbs_trace_syntax_element(ctx, position, name, 0LL, bits, value);
    }

    if (value >= range_min && value <= range_max)
    {
        *write_to = value;
        return 0;
    }
    else
    {
        av_log(ctx->log_ctx, AV_LOG_ERROR, "%s out of range: %u, but must be in [%u,%u].\n", 
               name, value, range_min, range_max);
        return CBS_BAD_VALUE;
    }
}