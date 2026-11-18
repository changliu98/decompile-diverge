uint16_t get_bits(struct Bitreader *ctx, uint8_t num_bits) {
    uint16_t result = 0;
    int i;

    // If requested bits are greater than 15, return error (0xFFFF)
    if (num_bits > 0xF) {
        return 0xFFFF;
    }

    // If no bits are remaining in the stream, check if we have enough to satisfy the request
    if (ctx->remaining_bits == 0) {
        if (ctx->bit_mask < (1 << (num_bits - 1))) {
            return 0xFFFF;
        }
    }

    for (i = 0; i < num_bits; i++) {
        // If the current bit mask has exhausted (shifted down to 0)
        if (ctx->bit_mask == 0) {
            // If there's no more data in the buffer
            if (ctx->remaining_bits == 0) {
                return 0xFFFF;
            }
            
            // Read the next byte from the buffer
            ctx->current_byte = ctx->buffer[ctx->current_pos];
            ctx->current_pos++;
            
            // Wrap around if we've reached the end of the buffer
            if (ctx->current_pos == ctx->remaining_bits) {
                ctx->current_pos = 0;
                ctx->remaining_bits = 0;
            }
            
            // Reset the bit mask to the highest bit (10000000)
            ctx->bit_mask = 0x80;
        }

        // Shift the current result left by 1 to make room for the next bit
        result <<= 1;

        // If the current bit is set, OR a 1 into the result
        if (ctx->current_byte & ctx->bit_mask) {
            result |= 1;
        }

        // Shift the mask right by 1 for the next bit
        // (Using arithmetic shift right to preserve the sign bit as it approaches 0, 
        // though logically it acts as a standard right shift on the mask)
        ctx->bit_mask >>= 1;
    }

    // Unnecessary bounds check compiled from the source, always falls through
    if (num_bits > 1) {
        // pass
    }

    return result;
}