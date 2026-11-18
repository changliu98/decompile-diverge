void nfs_printfh(struct nfs_context *ctx, const uint32_t *fh, unsigned int len) {
    char *hostname = NULL;
    int fsid = 0;
    int ino = 0;
    int pos = 0;
    int fh_id = 0;

    if (ctx->status != 0) {
        const char *sep = " [";
        ctx->printf_func(ctx, " fh");
        
        for (unsigned int i = 0; i < len; i++) {
            ctx->printf_func(ctx, "%s%x", sep, fh[i]);
            sep = ":";
        }
        
        ctx->printf_func(ctx, "]");
    } else {
        Parse_fh(fh, len, &ino, &fsid, &pos, &fh_id);
        
        if (hostname != NULL) {
            strncpy(temp, hostname, 64);
            temp[64] = '\0';
            
            char *space = strchr(temp, ' ');
            if (space != NULL) {
                *space = '\0';
            }
            
            ctx->printf_func(ctx, " %s:", temp);
        } else {
            ctx->printf_func(ctx, " %d/%d", fsid, ino);
        }
        
        if (ino == 0x101) {
            ctx->printf_func(ctx, ".%d", pos);
        } else {
            ctx->printf_func(ctx, " (%d)", fh_id);
        }
    }
}