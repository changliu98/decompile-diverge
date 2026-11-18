void sha256_update(struct sha256_ctx *ctx, const uint8_t *data, size_t len) {
    for (size_t i = 0; i < len; i++) {
        // Append the current byte into the buffer at the current length index
        ctx->buffer[ctx->buffer_len] = data[i];
        
        // Increment the buffer length
        ctx->buffer_len++;
        
        // If the buffer is full (64 bytes), process it
        if (ctx->buffer_len == 0x40) {
            // Transform the block. Note: The assembly passes `ctx` as both arguments.
            // This is typical when the transform function reads the block directly from the context.
            sha256_transform(ctx, (const uint8_t *)ctx);
            
            // Add 512 bits (0x200) to the total bit count
            ctx->bit_count += 0x200;
            
            // Reset the buffer length for the next chunk
            ctx->buffer_len = 0;
        }
    }
}