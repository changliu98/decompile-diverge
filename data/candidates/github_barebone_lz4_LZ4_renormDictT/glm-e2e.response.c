void LZ4_renormDictT(struct LZ4_stream_t_internal *ctx, uint32_t inputSize) {
    if (ctx->currentOffset + inputSize > 0x80000000) {
        uint32_t delta = ctx->currentOffset - 0x10000;
        const uint8_t *dictEnd = ctx->dictionary + ctx->dictSize;

        for (int i = 0; i < 0x1000; i++) {
            if (ctx->hashTable[i] < delta) {
                ctx->hashTable[i] = 0;
            } else {
                ctx->hashTable[i] -= delta;
            }
        }

        ctx->currentOffset = 0x10000;
        if (ctx->dictSize > 0x10000) {
            ctx->dictSize = 0x10000;
        }
        
        // Update the dictionary pointer to slide it down
        ctx->dictionary = dictEnd - ctx->dictSize;
    }
}