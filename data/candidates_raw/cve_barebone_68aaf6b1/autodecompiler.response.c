int ff_cbs_get_ue_golomb(CodedBitstreamContext *ctx,
                         GetBitContext *gbc,
                         const char *name,
                         unsigned int *value,
                         unsigned int min, unsigned int max)
{
    uint32_t buf;
    int len, start, i;
    int err;

    if (ctx->trace_enabled) {
        start = get_bits_count(gbc);
    }

    len = 0;
    while (1) {
        if (get_bits_left(gbc) < len + 1) {
            av_log(ctx->log_ctx, AV_LOG_ERROR,
                   "Invalid uvlc code at %s: bitstream ended.\n",
                   name);
            return -0x41444549;
        }
        buf = get_bits1(gbc);

        if (buf)
            break;

        ++len;
    }

    if (len > 31) {
        buf = -1;
    } else {
        buf = get_bits_long(gbc, len);

        for (i = 0; i < len; ++i) {
            buf <<= 1;
            buf += get_bits1(gbc);
        }
    }

    if (ctx->trace_enabled) {
        char symbol[64];
        symbol[len] = 0;
        for (i = 0; i < len; ++i)
            symbol[i] = get_bits1(gbc) ? '1' : '0';
        symbol[len] = 0;

        ff_cbs_trace_syntax_element(ctx, start, name, i, symbol, buf);
    }

    if (buf < min || buf > max) {
        av_log(ctx->log_ctx, AV_LOG_ERROR,
               "%s out of range: %u, but must be in [%u,%u].\n",
               name, buf, min, max);
        return -0x41444549;
    }

    *value = buf;

    return 0;
}