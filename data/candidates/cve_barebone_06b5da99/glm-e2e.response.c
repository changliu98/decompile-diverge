Main decompiled function
int zgfx_decompress_segment(ZGFX_CONTEXT* zgfx, void* stream, uint32_t segment_size) {
    int status = 0;
    uint32_t count = 0;
    uint32_t distance = 0;
    uint32_t token_index = 0;
    uint8_t flags = 0;
    uint8_t literal = 0;
    uint32_t segment_size_minus_1 = segment_size - 1;
    void* input_ptr = NULL;

    if (Stream_GetRemainingLength(stream) < segment_size || segment_size < 1) {
        return 0;
    }

    // Read flags byte
    flags = *(uint8_t*)Stream_Pointer(stream);
    Stream_Seek(stream, 1);
    zgfx->output_size = 0;

    input_ptr = Stream_Pointer(stream);
    Stream_Seek(stream, segment_size_minus_1);

    if ((flags & 0x20) == 0) {
        // Uncompressed segment
        zgfx_history_buffer_ring_write(zgfx, input_ptr, segment_size_minus_1);
        memcpy(zgfx->output_buffer, input_ptr, segment_size_minus_1);
        zgfx->output_size = segment_size_minus_1;
        return 1;
    } else {
        // Compressed segment
        zgfx->pb_input_current = input_ptr;
        zgfx->pb_input_end = input_ptr + segment_size_minus_1;
        zgfx->bits_remaining = (segment_size_minus_1 * 8) - *zgfx->pb_input_end;
        zgfx->bits_used = 0;
        zgfx->c_bits = 0;

        if (zgfx->bits_remaining == 0) {
            return 1;
        }

        while (ZGFX_TOKEN_TABLE[token_index].prefix_code != 0) {
            count = 0;
            distance = 0;

            // Match prefix code
            while (count < ZGFX_TOKEN_TABLE[token_index].prefix_code) {
                zgfx_GetBits(zgfx, 1);
                distance = (distance << 1) + zgfx->bits;
                count++;
            }

            if (distance == ZGFX_TOKEN_TABLE[token_index].prefix_length) {
                if (ZGFX_TOKEN_TABLE[token_index].token_type == 0) {
                    // Literal token
                    zgfx_GetBits(zgfx, ZGFX_TOKEN_TABLE[token_index].value_bits);
                    literal = (uint8_t)(ZGFX_TOKEN_TABLE[token_index].value_base + zgfx->bits);
                    
                    zgfx->history_buffer[zgfx->history_index] = literal;
                    zgfx->history_index++;
                    if (zgfx->history_index == zgfx->history_buffer_size) {
                        zgfx->history_index = 0;
                    }
                    
                    zgfx->output_buffer[zgfx->output_size] = literal;
                    zgfx->output_size++;
                } else {
                    // Match token
                    zgfx_GetBits(zgfx, ZGFX_TOKEN_TABLE[token_index].value_bits);
                    distance = ZGFX_TOKEN_TABLE[token_index].value_base + zgfx->bits;

                    if (distance != 0) {
                        zgfx_GetBits(zgfx, 1);
                        if (zgfx->bits == 0) {
                            count = 3;
                        } else {
                            count = 4;
                            int extra_bits = 2;
                            do {
                                zgfx_GetBits(zgfx, 1);
                                if (zgfx->bits != 1) break;
                                count <<= 1;
                                extra_bits++;
                            } while (1);
                            
                            zgfx_GetBits(zgfx, extra_bits);
                            count += zgfx->bits;
                        }

                        zgfx_history_buffer_ring_read(zgfx, distance, zgfx->output_buffer + zgfx->output_size, count);
                        zgfx_history_buffer_ring_write(zgfx, zgfx->output_buffer + zgfx->output_size, count);
                        zgfx->output_size += count;
                    } else {
                        // Raw segment / uncompressed block
                        zgfx_GetBits(zgfx, 15);
                        count = zgfx->bits;
                        
                        zgfx->bits_remaining -= zgfx->bits_used;
                        zgfx->bits_used = 0;
                        zgfx->c_bits = 0;

                        memcpy(zgfx->output_buffer + zgfx->output_size, zgfx->pb_input_current, count);
                        zgfx_history_buffer_ring_write(zgfx, zgfx->pb_input_current, count);
                        
                        zgfx->pb_input_current += count;
                        zgfx->bits_remaining -= count * 8;
                        zgfx->output_size += count;
                    }
                }
                break; // Break out of the token matching loop to process next token
            }
            token_index++;
        }
    }

    return 1;
}