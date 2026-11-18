void md_build_mark_char_map(MD_CTX *ctx)

{
  int i;
  MD_CTX *ctx_local;
  
  memset(ctx->mark_char_map,0,0x100);
  ctx->mark_char_map[0x5c] = '\x01';
  ctx->mark_char_map[0x2a] = '\x01';
  ctx->mark_char_map[0x5f] = '\x01';
  ctx->mark_char_map[0x60] = '\x01';
  ctx->mark_char_map[0x26] = '\x01';
  ctx->mark_char_map[0x3b] = '\x01';
  ctx->mark_char_map[0x3c] = '\x01';
  ctx->mark_char_map[0x3e] = '\x01';
  ctx->mark_char_map[0x5b] = '\x01';
  ctx->mark_char_map[0x21] = '\x01';
  ctx->mark_char_map[0x5d] = '\x01';
  ctx->mark_char_map[0] = '\x01';
  if (((ctx->parser).flags & 0x40200) != 0) {
    ctx->mark_char_map[0x7e] = '\x01';
  }
  if (((ctx->parser).flags & 0x20000) != 0) {
    ctx->mark_char_map[0x5e] = '\x01';
  }
  if (((ctx->parser).flags & 0x1000) != 0) {
    ctx->mark_char_map[0x24] = '\x01';
  }
  if (((ctx->parser).flags & 0x200000) != 0) {
    ctx->mark_char_map[0x3d] = '\x01';
  }
  if (((ctx->parser).flags & 8) != 0) {
    ctx->mark_char_map[0x40] = '\x01';
  }
  if (((ctx->parser).flags & 4) != 0) {
    ctx->mark_char_map[0x3a] = '\x01';
  }
  if (((ctx->parser).flags & 0x400) != 0) {
    ctx->mark_char_map[0x2e] = '\x01';
  }
  if (((((ctx->parser).flags & 0x100) != 0) || (((ctx->parser).flags & 0x2000) != 0)) ||
     (((ctx->parser).flags & 0x10000) != 0)) {
    ctx->mark_char_map[0x7c] = '\x01';
  }
  if (((ctx->parser).flags & 1) != 0) {
    for (i = 0; i < 0x100; i = i + 1) {
      if (((i == 0x20) || (i == 9)) || ((i == 0xb || (i == 0xc)))) {
        ctx->mark_char_map[i] = '\x01';
      }
    }
  }
  return;
}