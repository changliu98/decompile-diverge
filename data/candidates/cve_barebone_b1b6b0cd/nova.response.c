int read_new_config_info(struct cs_base64_ctx *ctx, struct cs_base64_decode_ctx *dctx) {
  int len = dctx->len;
  const char *in = dctx->in;

  ctx->error = 1;
  ctx->remainder = 0;
  ctx->remainder_size = 0;
  ctx->remainder_len = 0;

  while (len) {
    int i;
    int c;

    ctx->value = 0;
    ctx->bits = 0;

    while (len && (len >= 4 || ctx->bits < 24)) {
      c = *in++;
      ctx->value = (ctx->value << 6) | cs_base64_decode_value(c);
      ctx->bits += 6;
      len--;
    }

    if (len) {
      ctx->remainder_len = ctx->bits / 8;
      if (!ctx->remainder) {
        ctx->remainder = malloc(ctx->remainder_len + 1);
      }
      i = 0;
      while (len) {
        if (ctx->bits < 24) {
          ctx->remainder[i++] = (char)ctx->value;
        }
        ctx->value = (ctx->value >> 8);
        ctx->bits += 8;
        len--;
      }
      ctx->remainder_len = i;
    } else {
      ctx->remainder_len = ctx->bits / 8;
    }

    ctx->remainder_size += ctx->remainder_len;
  }

  return ctx->remainder_size;
}