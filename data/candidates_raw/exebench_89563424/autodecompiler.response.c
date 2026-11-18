void BTLZA_BitDec_RewindLastBit(BTLZA_Context *ctx)
{
 ctx->bs_pos=ctx->bs_pos_old;
 ctx->bs_win=ctx->bs_win_old;
}