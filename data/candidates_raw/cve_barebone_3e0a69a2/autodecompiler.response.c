__attribute__((used)) static int mpeg4_decode_studio_intra(Mpeg4DecContext *ctx, GetBitContext *gb)
{
    int i, j, val;

    if (get_bits1(gb)) {
        for (i = 0; i < 64; i++) {
            val = get_bits(gb, 8);
            j = ctx->scantable.permutated[ff_zigzag_direct[i]];
            ctx->block[j + 32] = ctx->block[j + 128] = val;
        }
    } else if (get_bits1(gb)) {
        for (i = 0; i < 64; i++) {
            val = get_bits(gb, 8);
            i++;
        }
    } else if (get_bits1(gb)) {
        for (i = 0; i < 64; i++) {
            val = get_bits(gb, 8);
            j = ctx->scantable.permutated[ff_zigzag_direct[i]];
            ctx->block[j + 128] = val;
        }
    } else if (get_bits1(gb)) {
        for (i = 0; i < 64; i++) {
            val = get_bits(gb, 8);
            i++;
        }
    }

    return next_start_code_studio(gb);
}