int iwgif_read_image(struct iwgif_context *ctx) {
  int result = 0;
  int min_code_size;
  int block_size;
  struct lzw_context lzw;
  if (iwgif_read(ctx, ctx->buffer, 9)) {
    ctx->left_position = iw_get_ui16le(ctx->buffer);
    ctx->top_position = iw_get_ui16le(ctx->buffer + 2);
    ctx->width = iw_get_ui16le(ctx->buffer + 4);
    ctx->height = iw_get_ui16le(ctx->buffer + 6);
    ctx->interlace = (ctx->buffer[8] & 0x40) ? 1 : 0;
    if (ctx->buffer[8] & 0x80) {
      ctx->screen.color_resolution = 1 << ((ctx->buffer[8] & 7) + 1);
      if (!iwgif_read_color_table(ctx, &ctx->screen)) return 0;
    }
    if (ctx->has_transparency)
      ctx->screen.colors[ctx->transparent_index].alpha = 0;
    if (iwgif_read(ctx, ctx->buffer, 1)) {
      min_code_size = ctx->buffer[0];
      if (min_code_size < 2 || min_code_size > 11) {
        iw_set_error(ctx->iw, "Invalid LZW minimum code size");
        return 0;
      }
      if (iwgif_init_screen(ctx)) {
        ctx->total_pixels = (long long)ctx->width * ctx->height;
        if (iwgif_make_row_pointers(ctx)) {
          lzw_init(&lzw, min_code_size);
          lzw_clear(&lzw);
          while (iwgif_read(ctx, ctx->buffer, 1)) {
            block_size = ctx->buffer[0];
            if (block_size == 0) {
              result = 1;
              break;
            }
            if (!iwgif_read(ctx, ctx->buffer, block_size)) return 0;
            if (lzw_process_bytes(ctx, &lzw, ctx->buffer, block_size)) {
              if (lzw.eof || ctx->pixel_count >= ctx->total_pixels) {
                result = 1;
                break;
              }
            } else {
              return 0;
            }
          }
        }
      }
    }
  }
  return result;
}