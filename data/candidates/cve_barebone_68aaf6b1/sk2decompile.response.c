static int cbs_av1_read_uvlc(CodedBitstreamContext *ctx, GetBitContext *gb,
                             const char *name, unsigned int *value,
                             unsigned int min, unsigned int max) {
  unsigned int v;
  int i, len, leading_zeros, ret;
  char buf[64];
  int pos;
  if (ctx->trace_enable) pos = get_bits_count(gb);
  len = 0;
  leading_zeros = 0;
  while (1) {
    if (get_bits_left(gb) < leading_zeros + 1) {
      av_log(ctx->avctx, 16, "Invalid uvlc code at %s: bitstream ended.\n",
             name);
      return -0x43332333;
    }
    if (get_bits1(gb)) {
      buf[len++] = '1';
      break;
    }
    buf[len++] = '0';
    leading_zeros++;
  }
  if (leading_zeros >= 32) {
    v = 0xffffffff;
  } else {
    v = get_bits_long(gb, leading_zeros);
    for (i = 0; i < leading_zeros; i++)
      buf[len++] = (v & (1 << (leading_zeros - i - 1))) ? '1' : '0';
    v += (1 << leading_zeros) - 1;
  }
  if (ctx->trace_enable) {
    buf[len] = 0;
    ff_cbs_trace_syntax_element(ctx, pos, name, 0, buf, v);
  }
  if (v < min || v > max) {
    av_log(ctx->avctx, 16, "%s out of range: %u, but must be in [%u,%u].\n",
           name, v, min, max);
    ret = -0x43332333;
  } else {
    *value = v;
    ret = 0;
  }
  return ret;
}