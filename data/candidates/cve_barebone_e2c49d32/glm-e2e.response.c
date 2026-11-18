int _gd2GetHeader(void *ctx, int *sx, int *sy, int *cs, int *vers, int *fmt, struct chunk **chunkList) {
    char sig[5];
    int i;
    int nc;
    int sz;
    struct chunk *chunks;

    for (i = 0; i < 4; i++) {
        int c = gdGetC(ctx);
        if (c == -1) {
            return 0;
        }
        sig[i] = (char)c;
    }
    sig[4] = '\0';

    if (strcmp(sig, "gd2") != 0) { // The string at 0x20e7 is inferred to be "gd2"
        return 0;
    }

    if (!gdGetWord(vers, ctx)) {
        return 0;
    }
    if (*vers != 1 && *vers != 2) {
        return 0;
    }

    if (!gdGetWord(sx, ctx)) {
        return 0;
    }
    if (!gdGetWord(sy, ctx)) {
        return 0;
    }
    if (!gdGetWord(cs, ctx)) {
        return 0;
    }
    if (*cs < 64 || *cs > 1024) {
        return 0;
    }

    if (!gdGetWord(fmt, ctx)) {
        return 0;
    }
    if (*fmt != 1 && *fmt != 2 && *fmt != 3 && *fmt != 4) {
        return 0;
    }

    if (!gdGetWord(sx, ctx)) { // Note: assembly reads into 0x10(%rbp) which is sx
        return 0;
    }
    if (!gdGetWord(sy, ctx)) { // Note: assembly reads into 0x18(%rbp) which is sy
        return 0;
    }

    if (*fmt == 2 || *fmt == 4) {
        nc = (*sx) * (*sy);
        if (!overflow2(nc, 8)) {
            return 0;
        }
        sz = nc * 8;
        if (sz <= 0) {
            return 0;
        }
        
        chunks = (struct chunk *)gdCalloc(sz, 1);
        if (chunks == NULL) {
            return 0;
        }

        for (i = 0; i < nc; i++) {
            if (!gdGetInt(&chunks[i].offset, ctx)) {
                gdFree(chunks);
                return 0;
            }
            if (!gdGetInt(&chunks[i].size, ctx)) {
                gdFree(chunks);
                return 0;
            }
            if (chunks[i].offset < 0 || chunks[i].size < 0) {
                gdFree(chunks);
                return 0;
            }
        }
        
        *chunkList = chunks;
    }

    return 1;
}