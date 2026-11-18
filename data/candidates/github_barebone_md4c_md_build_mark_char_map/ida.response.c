void __cdecl md_build_mark_char_map(MD_CTX *ctx)
{
  int i; // [rsp+4h] [rbp-Ch]

  memset(ctx->mark_char_map, 0, sizeof(ctx->mark_char_map));
  ctx->mark_char_map[92] = 1;
  ctx->mark_char_map[42] = 1;
  ctx->mark_char_map[95] = 1;
  ctx->mark_char_map[96] = 1;
  ctx->mark_char_map[38] = 1;
  ctx->mark_char_map[59] = 1;
  ctx->mark_char_map[60] = 1;
  ctx->mark_char_map[62] = 1;
  ctx->mark_char_map[91] = 1;
  ctx->mark_char_map[33] = 1;
  ctx->mark_char_map[93] = 1;
  ctx->mark_char_map[0] = 1;
  if ( (ctx->parser.flags & 0x40200) != 0 )
    ctx->mark_char_map[126] = 1;
  if ( (ctx->parser.flags & 0x20000) != 0 )
    ctx->mark_char_map[94] = 1;
  if ( (ctx->parser.flags & 0x1000) != 0 )
    ctx->mark_char_map[36] = 1;
  if ( (ctx->parser.flags & 0x200000) != 0 )
    ctx->mark_char_map[61] = 1;
  if ( (ctx->parser.flags & 8) != 0 )
    ctx->mark_char_map[64] = 1;
  if ( (ctx->parser.flags & 4) != 0 )
    ctx->mark_char_map[58] = 1;
  if ( (ctx->parser.flags & 0x400) != 0 )
    ctx->mark_char_map[46] = 1;
  if ( (ctx->parser.flags & 0x100) != 0 || (ctx->parser.flags & 0x2000) != 0 || (ctx->parser.flags & 0x10000) != 0 )
    ctx->mark_char_map[124] = 1;
  if ( (ctx->parser.flags & 1) != 0 )
  {
    for ( i = 0; i < 256; ++i )
    {
      if ( i == 32 || i == 9 || i == 11 || i == 12 )
        ctx->mark_char_map[i] = 1;
    }
  }
}