void md5_update(struct md5_ctx *ctx, const uint8_t *data, size_t len) {
    size_t i;
    for (i = 0; i < len; i++) {
        // Append the byte to the buffer
        ctx->buffer[ctx->buffer_idx] = data[i];
        
        // Increment the buffer index
        ctx->buffer_idx++;
        
        // If the buffer is full, process the block
        if (ctx->buffer_idx == 64) {
            // Note: The assembly passes ctx as both arguments (rdi and rsi).
            // This implies md5_transform likely reads the block directly from ctx->buffer.
            md5_transform(ctx, (const uint8_t *)ctx);
            
            // Update the total message length in bits (64 bytes * 8 bits = 512 bits = 0x200)
            ctx->bit_count += 0x200;
            
            // Reset the buffer index
            ctx->buffer_idx = 0;
        }
    }
}