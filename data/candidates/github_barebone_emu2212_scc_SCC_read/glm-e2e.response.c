int SCC_read(struct SCC_ctx *ctx, unsigned int offset) {
    int ret;

    // Check for specific condition at offset 0x14 and masked offset
    if (ctx->field_0x14 == 1 && (offset & 0xfffe) == 0xbffe) {
        ret = (ctx->field_0x20 >> 8) & 0x20;
        return ret;
    }

    // Check if offset is less than field_0x20
    if (offset < ctx->field_0x20) {
        return 0;
    }

    // Adjust offset
    offset -= ctx->field_0x20;

    if (offset == 0) {
        // Check field_0x18
        if (ctx->field_0x18 != 0) {
            return 0x80;
        } else {
            return 0x3f;
        }
    }

    // Check field_0x1c and offset bounds
    if (ctx->field_0x1c != 0 && offset >= 0x800 && 0x8ff < offset) {
        return 0;
    }

    // Switch-like structure based on field_0x14
    switch (ctx->field_0x14) {
        case 0:
            return read_standard(ctx, offset);
        case 1:
            if (ctx->field_0x18 == 0) {
                return read_standard(ctx, offset);
            } else {
                return read_enhanced(ctx, offset);
            }
        default:
            return 0;
    }
}