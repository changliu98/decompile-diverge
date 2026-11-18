void aodv_extension(struct aodv_struct *ctx, uint8_t *ext, uint64_t ext_len) {
    if (ext[0] - 1 == 0) {
        uint8_t *p = ext;
        
        // Bounds and length checks
        if (ctx->total_len - 6 > ctx->total_len || p > ctx->total_len - 6) {
            ctx->log_func("Invalid length");
        } else if (ext_len < 6) {
            ctx->log_func("Invalid length");
        } else {
            // Extract a 32-bit big-endian integer from bytes 2 to 5
            uint32_t val = ((uint32_t)p[2] << 24) |
                           ((uint32_t)p[3] << 16) |
                           ((uint32_t)p[4] << 8)  |
                           ((uint32_t)p[5]);
            
            ctx->log_func("AODV extension type %d, length %d, value %u", p[0], p[1], val);
        }
    } else {
        ctx->log_func("Unknown extension type %d, length %d", ext[0], ext[1]);
    }
}