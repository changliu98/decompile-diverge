int __cdecl cbs_av1_read_uvlc(
        CodedBitstreamContext *ctx,
        GetBitContext *gbc,
        const char *name,
        uint32_t *write_to,
        uint32_t range_min,
        uint32_t range_max)
{
  int bits_left; // eax
  int v7; // eax
  int v8; // eax
  char v9; // al
  char v10; // cl
  int v11; // eax
  uint32_t v13; // [rsp+0h] [rbp-A0h]
  char bits[65]; // [rsp+10h] [rbp-90h] BYREF
  int j; // [rsp+5Ch] [rbp-44h]
  int i; // [rsp+60h] [rbp-40h]
  int zeroes; // [rsp+64h] [rbp-3Ch]
  int position; // [rsp+68h] [rbp-38h]
  uint32_t value; // [rsp+6Ch] [rbp-34h]
  uint32_t range_maxa; // [rsp+70h] [rbp-30h]
  uint32_t range_mina; // [rsp+74h] [rbp-2Ch]
  uint32_t *write_toa; // [rsp+78h] [rbp-28h]
  const char *namea; // [rsp+80h] [rbp-20h]
  GetBitContext *gbca; // [rsp+88h] [rbp-18h]
  CodedBitstreamContext *ctxa; // [rsp+90h] [rbp-10h]

  ctxa = ctx;
  gbca = gbc;
  namea = name;
  write_toa = write_to;
  range_mina = range_min;
  range_maxa = range_max;
  if ( ctx->trace_enable )
    position = get_bits_count(gbca);
  i = 0;
  for ( zeroes = 0; ; ++zeroes )
  {
    bits_left = get_bits_left(gbca);
    if ( bits_left < zeroes + 1 )
    {
      av_log(ctxa->log_ctx, 16, "Invalid uvlc code at %s: bitstream ended.\n", namea);
      return -1094995529;
    }
    if ( get_bits1(gbca) )
      break;
    v8 = i++;
    bits[v8] = 48;
  }
  v7 = i++;
  bits[v7] = 49;
  if ( zeroes < 32 )
  {
    value = get_bits_long(gbca, zeroes);
    for ( j = 0; j < zeroes; ++j )
    {
      v9 = 48;
      if ( ((value >> (zeroes - j - 1)) & 1) != 0 )
        v9 = 49;
      v10 = v9;
      v11 = i++;
      bits[v11] = v10;
    }
    value += (1 << zeroes) - 1;
  }
  else
  {
    value = -1;
  }
  if ( ctxa->trace_enable )
  {
    bits[i] = 0;
    ff_cbs_trace_syntax_element(ctxa, position, namea, 0LL, bits, value);
  }
  if ( value >= range_mina && value <= range_maxa )
  {
    *write_toa = value;
    return 0;
  }
  else
  {
    v13 = range_maxa;
    av_log(ctxa->log_ctx, 16, "%s out of range: %u, but must be in [%u,%u].\n", namea, value, range_mina, v13);
    return -1094995529;
  }
}