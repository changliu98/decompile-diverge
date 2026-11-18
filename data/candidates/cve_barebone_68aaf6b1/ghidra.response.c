int cbs_av1_read_uvlc(CodedBitstreamContext *ctx,GetBitContext *gbc,char *name,uint32_t *write_to,
                     uint32_t range_min,uint32_t range_max)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  char bits [65];
  int j;
  int i;
  int zeroes;
  int position;
  uint32_t value;
  uint32_t range_max_local;
  uint32_t range_min_local;
  uint32_t *write_to_local;
  char *name_local;
  GetBitContext *gbc_local;
  CodedBitstreamContext *ctx_local;
  
  if (ctx->trace_enable != 0) {
    position = get_bits_count(gbc);
  }
  i = 0;
  zeroes = 0;
  while( true ) {
    iVar2 = get_bits_left(gbc);
    if (iVar2 < zeroes + 1) {
      av_log(ctx->log_ctx,0x10,"Invalid uvlc code at %s: bitstream ended.\n",name);
      return -0x41444e49;
    }
    uVar3 = get_bits1(gbc);
    if (uVar3 != 0) break;
    bits[i] = '0';
    zeroes = zeroes + 1;
    i = i + 1;
  }
  bits[i] = '1';
  if (zeroes < 0x20) {
    uVar3 = get_bits_long(gbc,zeroes);
    i = i + 1;
    for (j = 0; j < zeroes; j = j + 1) {
      cVar1 = '0';
      if ((uVar3 >> (((byte)zeroes - (char)j) - 1 & 0x1f) & 1) != 0) {
        cVar1 = '1';
      }
      bits[i] = cVar1;
      i = i + 1;
    }
    value = (1 << ((byte)zeroes & 0x1f)) + -1 + uVar3;
  }
  else {
    value = 0xffffffff;
    i = i + 1;
  }
  if (ctx->trace_enable != 0) {
    bits[i] = '\0';
    ff_cbs_trace_syntax_element(ctx,position,name,(int *)0x0,bits,(ulong)value);
  }
  if ((range_min <= value) && (value <= range_max)) {
    *write_to = value;
    return 0;
  }
  av_log(ctx->log_ctx,0x10,"%s out of range: %u, but must be in [%u,%u].\n",name,(ulong)value,
         (ulong)range_min,range_max);
  return -0x41444e49;
}