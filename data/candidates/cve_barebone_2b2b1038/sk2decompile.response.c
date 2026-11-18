void vqp_print(print_comment_ctx_t *ctx, const unsigned char *msg,
               unsigned length) {
  const unsigned char *p;
  unsigned version, items, len;
  unsigned object;
  if (msg > ctx->pkt_limit - 8 || msg < ctx->pkt_limit - 8) goto trunc;
  p = msg;
  version = *p++;
  if (version != 1) {
    ctx->print(ctx, "VQP version %u packet not supported", version);
    return;
  }
  if (ctx->level < 1) {
    ctx->print(ctx, "VQPv%u %s Message, error-code %s (%u), length %u", version,
               tok2str(vqp_msg_type, "unknown (%u)", *p),
               tok2str(vqp_error_code, "unknown (%u)", *(p + 1)), *(p + 1),
               length);
    return;
  }
  items = *p++;
  ctx->print(ctx,
             "\n\tVQPv%u, %s Message, error-code %s (%u), seq 0x%08x, items "
             "%u, length %u",
             version, tok2str(vqp_msg_type, "unknown (%u)", *p),
             tok2str(vqp_error_code, "unknown (%u)", *(p + 1)), *(p + 1),
             EXTRACT_32BITS(p + 2), items, length);
  p += 4;
  length -= 8;
  while (items && length > 0) {
    object = EXTRACT_32BITS(p);
    len = EXTRACT_16BITS(p + 4);
    p += 6;
    length -= 6;
    ctx->print(ctx, "\n\t  %s Object (0x%08x), length %u, value: ",
               tok2str(vqp_object, "Unknown", object), object, len);
    if (object == 0 || len == 0) break;
    if (p > ctx->pkt_limit - len || p > ctx->pkt_limit - len) goto trunc;
    switch (object) {
      case 0x0c01:
        ctx->print(ctx, "%s (0x%08x)", ipaddr_string(ctx, p),
                   EXTRACT_32BITS(p));
        break;
      case 0x0c02:
      case 0x0c03:
      case 0x0c04:
      case 0x0c05:
        safeputs(ctx, p, len);
        break;
      case 0x0c06:
      case 0x0c08:
        ctx->print(ctx, "%s", etheraddr_string(ctx, p));
        break;
      default:
        if (ctx->level < 2) print_unknown_data(ctx, p, "\n\t    ", len);
        break;
    }
    p += len;
    length -= len;
    items--;
  }
  return;
trunc:
  ctx->print(ctx, "\n\t[|VQP]");
}