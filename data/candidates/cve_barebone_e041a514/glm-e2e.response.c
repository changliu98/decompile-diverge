int _gd2GetHeader(gdIOCtx *ctx, int *sx, int *sy, int *cs, int *vers, int *fmt, struct ChunkInfo **chunks) {
    char signature[5];
    int i;
    int total_chunks;
    int alloc_size;
    struct ChunkInfo *chunk_arr;

    // Read 4-byte signature
    for (i = 0; i < 4; i++) {
        int c = gdGetC(ctx);
        if (c == -1) {
            return 0;
        }
        signature[i] = (char)c;
    }
    signature[4] = '\0';

    // Validate signature
    if (strcmp(signature, "gd2_") != 0) { // String located at 0x2020
        return 0;
    }

    // Read and validate version
    if (gdGetWord(vers, ctx) != 1) {
        return 0;
    }
    if (*vers != 1 && *vers != 2) {
        return 0;
    }

    // Read width and height
    if (gdGetWord(sx, ctx) == 0) {
        return 0;
    }
    if (gdGetWord(sy, ctx) == 0) {
        return 0;
    }

    // Read and validate chunk size
    if (gdGetWord(cs, ctx) != 1) {
        return 0;
    }
    if (*cs < 64 || *cs > 4096) {
        return 0;
    }

    // Read and validate format
    if (gdGetWord(fmt, ctx) != 1) {
        return 0;
    }
    if (*fmt != 1 && *fmt != 2 && *fmt != 3 && *fmt != 4) {
        return 0;
    }

    // Read x and y chunk counts (stored in stack-allocated variables)
    int x_chunks, y_chunks;
    if (gdGetWord(&x_chunks, ctx) != 1) {
        return 0;
    }
    if (gdGetWord(&y_chunks, ctx) != 1) {
        return 0;
    }

    // If format is compressed (2 or 4), read the chunk offset/size table
    if (*fmt == 2 || *fmt == 4) {
        total_chunks = x_chunks * y_chunks;
        alloc_size = total_chunks * 8; // 8 bytes per chunk info (2 ints)

        if (alloc_size <= 0) {
            return 0;
        }

        chunk_arr = (struct ChunkInfo *)calloc(1, alloc_size);
        if (chunk_arr == NULL) {
            return 0;
        }

        for (i = 0; i < total_chunks; i++) {
            if (gdGetInt(&chunk_arr[i].offset, ctx) != 1) {
                free(chunk_arr);
                return 0;
            }
            if (gdGetInt(&chunk_arr[i].size, ctx) != 1) {
                free(chunk_arr);
                return 0;
            }
            if (chunk_arr[i].offset < 0 || chunk_arr[i].size < 0) {
                free(chunk_arr);
                return 0;
            }
        }

        *chunks = chunk_arr;
    }

    return 1;
}