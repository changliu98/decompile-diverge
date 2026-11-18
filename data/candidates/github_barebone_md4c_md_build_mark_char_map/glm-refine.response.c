void __cdecl md_build_mark_char_map(MD_CTX *ctx)
{
  int i;

  memset(ctx->mark_char_map, 0, sizeof(ctx->mark_char_map));

  // Common Markdown punctuation and control characters
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

  // Conditionally enabled characters based on parser flags
  if (ctx->parser.flags & (MD_FLAG_STRIKETHROUGH | MD_FLAG_LATEXMATHSPANS))
    ctx->mark_char_map['~'] = 1;

  if (ctx->parser.flags & MD_FLAG_SUPERSCRIPT)
    ctx->mark_char_map['^'] = 1;

  if (ctx->parser.flags & MD_FLAG_LATEXMATHSPANS)
    ctx->mark_char_map['$'] = 1;

  if (ctx->parser.flags & MD_FLAG_UNDERLINE)
    ctx->mark_char_map['='] = 1;

  if (ctx->parser.flags & MD_FLAG_WIKILINKS)
    ctx->mark_char_map['@'] = 1;

  if (ctx->parser.flags & MD_FLAG_PERMISSIVEURLAUTOLINKS)
    ctx->mark_char_map[':'] = 1;

  if (ctx->parser.flags & MD_FLAG_PERMISSIVEEMAILAUTOLINKS)
    ctx->mark_char_map['.'] = 1;

  if (ctx->parser.flags & (MD_FLAG_TABLES | MD_FLAG_TASKLISTS | MD_FLAG_MULTILINE_TABLES))
    ctx->mark_char_map['|'] = 1;

  // Whitespace characters
  if (ctx->parser.flags & MD_FLAG_COLLAPSEWHITESPACE)
  {
    for (i = 0; i < 256; ++i)
    {
      if (i == ' ' || i == '\t' || i == '\v' || i == '\f')
        ctx->mark_char_map[i] = 1;
    }
  }
}