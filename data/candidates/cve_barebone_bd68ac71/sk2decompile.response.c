gfsize BS_ReadByte(BS_Context *ctx) {
  gfsize b;
  gfint err;
  if (ctx->write_mode == 0) {
    if (ctx->pos >= ctx->size) {
      if (ctx->error_handler) ctx->error_handler(ctx->error_handler_data);
      if (ctx->error_flag == 0) ctx->error_flag = 1;
      return 0;
    }
    b = ctx->buffer[ctx->pos++];
    if (ctx->check_for_eof) {
      if (ctx->eof_count == 2 && b == 3 && ctx->pos < ctx->size &&
          ctx->buffer[ctx->pos] < 4) {
        ctx->eof_count = 0;
        b = ctx->buffer[ctx->pos++];
      }
      if (b == 0)
        ctx->eof_count++;
      else
        ctx->eof_count = 0;
    }
    return b;
  }
  if (ctx->write_cache_pos) bs_flush_write_cache(ctx);
  err = gf_feof(ctx->fp);
  if (err && !ctx->allow_write_past_end) {
    if (ctx->error_handler) {
      ctx->error_handler(ctx->error_handler_data);
      if (ctx->error_flag == 0) ctx->error_flag = 1;
    }
    if (ctx->pos > 1 + ctx->size) {
      assert(ctx->pos <= 1 + ctx->size);
    }
    return 0;
  }
  err = GF_FALSE;
  assert(ctx->pos <= ctx->size);
  ctx->pos++;
  b = gf_bs_load_byte(ctx, &err);
  if (err) {
    if (ctx->error_handler) {
      ctx->error_handler(ctx->error_handler_data);
      if (ctx->error_flag == 0) ctx->error_flag = 1;
    }
    if (ctx->pos > 1 + ctx->size) {
      assert(ctx->pos <= 1 + ctx->size);
    }
    return 0;
  }
  if (ctx->check_for_eof) {
    if (ctx->eof_count == 2 && b == 3 && ctx->pos < ctx->size) {
      gfsize b2 = gf_bs_load_byte(ctx, &err);
      if (b2 < 4) {
        ctx->eof_count = 0;
        b = b2;
        ctx->pos++;
      } else {
        gf_bs_seek(ctx, ctx->pos);
      }
    }
    if (b == 0)
      ctx->eof_count++;
    else
      ctx->eof_count = 0;
  }
  return b;
}