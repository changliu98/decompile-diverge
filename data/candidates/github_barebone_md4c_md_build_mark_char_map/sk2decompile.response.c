static void md_build_mark_char_map(MD_CTX *ctx) {
  int i;
  memset(ctx->mark_char_map, 0, sizeof(ctx->mark_char_map));
  ctx->mark_char_map['\\'] = 1;
  ctx->mark_char_map['*'] = 1;
  ctx->mark_char_map['_'] = 1;
  ctx->mark_char_map['`'] = 1;
  ctx->mark_char_map['&'] = 1;
  ctx->mark_char_map[';'] = 1;
  ctx->mark_char_map['<'] = 1;
  ctx->mark_char_map['>'] = 1;
  ctx->mark_char_map['['] = 1;
  ctx->mark_char_map['!'] = 1;
  ctx->mark_char_map[']'] = 1;
  ctx->mark_char_map['\0'] = 1;
  if (ctx->options.extensions & (1 << 17)) ctx->mark_char_map['~'] = 1;
  if (ctx->options.extensions & (1 << 18)) ctx->mark_char_map['^'] = 1;
  if (ctx->options.extensions & (1 << 12)) ctx->mark_char_map['$'] = 1;
  if (ctx->options.extensions & (1 << 21)) ctx->mark_char_map['='] = 1;
  if (ctx->options.extensions & (1 << 3)) ctx->mark_char_map['@'] = 1;
  if (ctx->options.extensions & (1 << 2)) ctx->mark_char_map[':'] = 1;
  if (ctx->options.extensions & (1 << 10)) ctx->mark_char_map['.'] = 1;
  if (ctx->options.extensions & (1 << 8) || ctx->options.extensions & (1 << 13) ||
      ctx->options.extensions & (1 << 16))
    ctx->mark_char_map['|'] = 1;
  if (ctx->options.extensions & (1 << 0)) {
    for (i = 0; i < 256; i++) {
      if (i == ' ' || i == '\t' || i == '\v' || i == '\f')
        ctx->mark_char_map[i] = 1;
    }
  }
}