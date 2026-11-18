void ZSTD_freeCCtx(ZSTD_CCtx* cctx)
{
    if (!cctx) return;   /* support free on NULL */
    DEBUGLOG(3, "ZSTD_freeCCtx %p", cctx);
    cctx->staticSize -= sizeof(ZSTD_CCtx);  /* don't count this */
    if (cctx->staticSize) {
        assert(cctx->customMem.customFree && cctx->customMem.customAlloc);
        cctx->customMem.customFree(cctx->customMem.customAllocParameter, cctx);
        return;
    }
    if (cctx->customMem.customFree) {
        cctx->customMem.customFree(cctx->customMem.customAllocParameter, cctx);
    } else {
        free(cctx);
    }
}