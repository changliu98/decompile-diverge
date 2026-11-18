static int am_writestring(am_DumpCtx *ctx, const char *name) {
    am_Dumper *d = ctx->dumper;
    size_t namelen = (name ? strlen(name) : 0), buflen;
    amC(namelen < AM_NAME_LEN && namelen <= 0xFF);
    if (namelen < 32)
        amE(am_writechar(ctx, 0xA0 + (int)namelen));
    else {
        amE(am_writechar(ctx, 0xD9));
        amE(am_writechar(ctx, (int)namelen));
    }
    if ((buflen = (ctx->p - ctx->buf)) + namelen > AM_BUF_LEN) {
        ctx->p = ctx->buf;
        if (buflen) amE(ctx->ret = d->writer(d, ctx->buf, buflen));
        if (namelen > AM_BUF_LEN) return ctx->ret = d->writer(d, name, namelen);
    }
    memcpy(ctx->p, name, namelen);
    return ctx->p += namelen, AM_OK;
}