void Z80_RES5A(Z80Context* ctx)
{
    ctx->A &= ~0x20;
    ctx->F = (ctx->A == 0) ? (ctx->F | 0x80) : (ctx->F & ~0x80);;
    ctx->F = (ctx->A & 0x10) ? (ctx->F | 0x04) : (ctx->F & ~0x04);;
}