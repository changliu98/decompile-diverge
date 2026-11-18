define AV_LOG_DEBUG 16

int cbs_av1_read_uvlc(CodedBitstreamContext *ctx, GetBitContext *gbc, 
                      const char *name, int *write_to, uint32_t range_min, uint32_t range_max) {
    int position;
    int n; // -0x40(%rbp)
    int k; // -0x3c(%rbp)
    int value; // -0x34(%rbp)
    int i; // -0x44(%rbp)
    char bits[80]; // -0x90(%rbp) to -0x40(%rbp)

    if (ctx->trace_enable) { // 0x8(%rax)
        position = get_bits_count(gbc);
    }

    n = 0;
    k = 0;

    while (1) {
        if (get_bits_left(gbc) < k + 1) {
            av_log(ctx->log_ctx, AV_LOG_DEBUG, "uvlc: Invalid %s: bitstream ended.\n", name);
            return AVERROR_INVALIDDATA; // 0xbebbb1b7
        }

        if (get_bits1(gbc)) {
            bits[n++] = '1';
            break;
        } else {
            bits[n++] = '0';
            k++;
        }

        if (k >= 32) {
            value = -1;
            goto trace_and_validate;
        }
    }

    value = get_bits_long(gbc, k);

    for (i = 0; i < k; i++) {
        bits[n++] = (value >> (k - i - 1)) & 1 ? '1' : '0';
    }

    value += (1 << k) - 1;

trace_and_validate:
    if (ctx->trace_enable) {
        bits[n] = '\0';
        ff_cbs_trace_syntax_element(ctx, position, name, bits, value, 0);
    }

    if ((uint32_t)value < range_min || (uint32_t)value > range_max) {
        av_log(ctx->log_ctx, AV_LOG_DEBUG, "uvlc: Invalid %s: value out of range (%d < %d > %d).\n", 
               name, value, range_min, range_max);
        return AVERROR_INVALIDDATA; // 0xbebbb1b7
    }

    *write_to = value;
    return 0;
}