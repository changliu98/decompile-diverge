void md_build_mark_char_map(struct md_context *ctx)
{
  int i;
  md_setzero(ctx->mark_char_map, 0, sizeof(ctx->mark_char_map));
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
  ctx->mark_char_map[' '] = 1;
  if (ctx->parser.flags & (MD_F_EXT1 | MD_F_EXT2 | MD_F_EXT3))
    ctx->mark_char_map['~'] = 1;
  if (ctx->parser.flags & MD_F_EXT1)
    ctx->mark_char_map['^'] = 1;
  if (ctx->parser.flags & MD_F_EXT2)
    ctx->mark_char_map['$'] = 1;
  if (ctx->parser.flags & MD_F_EXT3)
    ctx->mark_char_map['='] = 1;
  if (ctx->parser.flags & MD_F_EXT4)
    ctx->mark_char_map['@'] = 1;
  if (ctx->parser.flags & MD_F_EXT5)
    ctx->mark_char_map[':'] = 1;
  if (ctx->parser.flags & MD_F_EXT6)
    ctx->mark_char_map['.'] = 1;
  if (ctx->parser.flags & (MD_F_EXT7 | MD_F_EXT8 | MD_F_EXT9))
    ctx->mark_char_map['|'] = 1;
  if (ctx->parser.flags & MD_F_EXT10)
  {
    for (i = 0; i < 256; i++)
    {
      if (i == ' ' || i == '\t' || i == '\v' || i == '\f')
        ctx->mark_char_map[i] = 1;
    }
  }
}