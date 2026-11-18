void md_build_mark_char_map(struct MD_CTX *ctx) {
    memset(ctx->mark_char_map, 0, 256);

    ctx->mark_char_map[0x5c] = 1; // 0x13c - 0xe0
    ctx->mark_char_map[0x2a] = 1; // 0x10a - 0xe0
    ctx->mark_char_map[0x5f] = 1; // 0x13f - 0xe0
    ctx->mark_char_map[0x60] = 1; // 0x140 - 0xe0
    ctx->mark_char_map[0x26] = 1; // 0x106 - 0xe0
    ctx->mark_char_map[0x3b] = 1; // 0x11b - 0xe0
    ctx->mark_char_map[0x3c] = 1; // 0x11c - 0xe0
    ctx->mark_char_map[0x3e] = 1; // 0x11e - 0xe0
    ctx->mark_char_map[0x5b] = 1; // 0x13b - 0xe0
    ctx->mark_char_map[0x21] = 1; // 0x101 - 0xe0
    ctx->mark_char_map[0x5d] = 1; // 0x13d - 0xe0
    ctx->mark_char_map[0x00] = 1; // 0xe0 - 0xe0

    if ((ctx->flags & 0x40200) != 0) {
        ctx->mark_char_map[0x7e] = 1; // 0x15e - 0xe0
    }
    if ((ctx->flags & 0x20000) != 0) {
        ctx->mark_char_map[0x5e] = 1; // 0x13e - 0xe0
    }
    if ((ctx->flags & 0x1000) != 0) {
        ctx->mark_char_map[0x24] = 1; // 0x104 - 0xe0
    }
    if ((ctx->flags & 0x200000) != 0) {
        ctx->mark_char_map[0x3d] = 1; // 0x11d - 0xe0
    }
    if ((ctx->flags & 0x8) != 0) {
        ctx->mark_char_map[0x40] = 1; // 0x120 - 0xe0
    }
    if ((ctx->flags & 0x4) != 0) {
        ctx->mark_char_map[0x3a] = 1; // 0x11a - 0xe0
    }
    if ((ctx->flags & 0x400) != 0) {
        ctx->mark_char_map[0x2e] = 1; // 0x10e - 0xe0
    }
    if ((ctx->flags & 0x100) != 0 || (ctx->flags & 0x2000) != 0 || (ctx->flags & 0x10000) != 0) {
        ctx->mark_char_map[0x7c] = 1; // 0x15c - 0xe0
    }

    if ((ctx->flags & 0x1) != 0) {
        for (int i = 0; i < 256; i++) {
            if (i == 0x20 || i == 0x9 || i == 0xb || i == 0xc) {
                ctx->mark_char_map[i] = 1;
            }
        }
    }
}