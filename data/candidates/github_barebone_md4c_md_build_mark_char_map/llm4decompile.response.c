void
md_build_mark_char_map(MD_CTX* ctx)
{
    memset(ctx->mark_char_map, 0, 256);

    ctx->mark_char_map['\\'] = 1;
    ctx->mark_char_map['`'] = 1;
    ctx->mark_char_map['*'] = 1;
    ctx->mark_char_map['_'] = 1;
    ctx->mark_char_map['&'] = 1;
    ctx->mark_char_map['<'] = 1;
    ctx->mark_char_map['>'] = 1;
    ctx->mark_char_map['['] = 1;
    ctx->mark_char_map[']'] = 1;
    ctx->mark_char_map[';'] = 1;
    ctx->mark_char_map['!'] = 1;
    ctx->mark_char_map['\0'] = 1;

    if(ctx->parser.flags & (0x00040000 | 0x00000200))
        ctx->mark_char_map['~'] = 1;
    if(ctx->parser.flags & 0x00020000)
        ctx->mark_char_map['^'] = 1;
    if(ctx->parser.flags & 0x00001000)
        ctx->mark_char_map['$'] = 1;
    if(ctx->parser.flags & 0x000200000)
        ctx->mark_char_map['='] = 1;
    if(ctx->parser.flags & 0x00000008)
        ctx->mark_char_map['@'] = 1;
    if(ctx->parser.flags & 0x00000004)
        ctx->mark_char_map[':'] = 1;
    if(ctx->parser.flags & 0x00000400)
        ctx->mark_char_map['.'] = 1;
    if(ctx->parser.flags & 0x00000100 ||
       ctx->parser.flags & 0x00002000 ||
       ctx->parser.flags & 0x00010000)
        ctx->mark_char_map['|'] = 1;

    if(ctx->parser.flags & 0x00000001) {
        int i;
        for(i=0; i<256; i++) {
            if(i == ' ' || i == '\t' || i == '\v' || i == '\f')
                ctx->mark_char_map[i] = 1;
        }
    }
}