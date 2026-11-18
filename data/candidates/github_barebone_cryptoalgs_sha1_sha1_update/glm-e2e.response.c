void sha1_update(SHA1_CTX *ctx, const uint8_t *data, size_t len) {
    for (size_t i = 0; i < len; i++) {
        // Append the byte to the context's buffer
        ctx->buffer[ctx->buffer_len] = data[i];
        ctx->buffer_len++;

        // If the buffer is full (64 bytes), process it
        if (ctx->buffer_len == 0x40) {
            // Pass the context as both the state and the data source for transformation
            sha1_transform(ctx, (const uint8_t *)ctx);
            
            // Add 512 bits (0x200 bits = 64 bytes) to the total processed length
            ctx->total_len += 0x200;
            
            // Reset the buffer length
            ctx->buffer_len = 0;
        }
    }
}