static BOOL zgfx_decompress_segment(ZGfx_Decompress_Context* ctx,
                                    Stream_t* stream, u32 length) {
  unsigned char flags;
  unsigned char* start;
  unsigned int i;
  length--;
  if (Stream_GetRemainingLength(stream) < length || length == 0) return 0;
  flags = *stream->ptr;
  Stream_Seek(stream, 1);
  ctx->output_length = 0;
  start = Stream_Pointer(stream);
  Stream_Seek(stream, length);
  if (!(flags & 0x20)) {
    zgfx_history_buffer_ring_write(ctx, start, length);
    memcpy(ctx->output_buffer, start, length);
    ctx->output_length = length;
    return 1;
  }
  ctx->input_ptr = start;
  ctx->input_end = start + length - 1;
  ctx->input_bits_left = (length - 1) * 8 - *ctx->input_end;
  ctx->input_bits_read = 0;
  ctx->input_bits_read_this_byte = 0;
  while (ctx->input_bits_left) {
    unsigned int bits_read = 0;
    unsigned int code = 0;
    int ix;
    for (ix = 0; zgfx_codes[ix].bits; ix++) {
      while (bits_read < zgfx_codes[ix].bits) {
        zgfx_GetBits(ctx, 1);
        code = (code << 1) + ctx->bit_buffer;
        bits_read++;
      }
      if (code == zgfx_codes[ix].code) {
        if (zgfx_codes[ix].is_copy) {
          unsigned int copy_length;
          int copy_offset;
          int copy_offset_bits;
          zgfx_GetBits(ctx, zgfx_codes[ix].copy_offset_bits);
          copy_offset = ctx->bit_buffer + zgfx_codes[ix].copy_offset_value;
          if (copy_offset == 0) {
            zgfx_GetBits(ctx, 15);
            copy_length = ctx->bit_buffer;
            ctx->input_bits_left -= ctx->input_bits_read;
            ctx->input_bits_read = 0;
            ctx->input_bits_read_this_byte = 0;
            memcpy(ctx->output_buffer + ctx->output_length, ctx->input_ptr,
                   copy_length);
            zgfx_history_buffer_ring_write(ctx, ctx->input_ptr, copy_length);
            ctx->input_ptr += copy_length;
            ctx->input_bits_left -= copy_length * 8;
            ctx->output_length += copy_length;
          } else {
            copy_length = 4;
            copy_offset_bits = 2;
            zgfx_GetBits(ctx, 1);
            while (ctx->bit_buffer == 1) {
              copy_length *= 2;
              copy_offset_bits++;
              zgfx_GetBits(ctx, 1);
            }
            zgfx_GetBits(ctx, copy_offset_bits);
            copy_length += ctx->bit_buffer;
            zgfx_history_buffer_ring_read(
                ctx, copy_offset, ctx->output_buffer + ctx->output_length,
                copy_length);
            zgfx_history_buffer_ring_write(
                ctx, ctx->output_buffer + ctx->output_length, copy_length);
            ctx->output_length += copy_length;
          }
        } else {
          unsigned char value;
          zgfx_GetBits(ctx, zgfx_codes[ix].copy_offset_bits);
          value = ctx->bit_buffer + zgfx_codes[ix].copy_offset_value;
          ctx->history_buffer[ctx->history_buffer_write_index] = value;
          ctx->history_buffer_write_index++;
          if (ctx->history_buffer_write_index == ctx->history_buffer_size)
            ctx->history_buffer_write_index = 0;
          ctx->output_buffer[ctx->output_length++] = value;
        }
        break;
      }
    }
  }
  return 1;
}