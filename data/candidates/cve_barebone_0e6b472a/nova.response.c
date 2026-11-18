int AVI_read_audio(struct cs_base64_ctx *ctx, const char *src, int src_len, int *dst_len) {
  int i, j, k, l, m, n;
  unsigned long long x, y;

  if (!ctx->initialized) {
    ctx->decoding_table[62] = 62;
    i = -1;
  } else {
    if (ctx->encoding_table[62] == 0) {
      ctx->encoding_table[62] = 13;
      i = -1;
    } else {
      i = 0;
    }
  }

  while (1) {
    while (i < src_len && src[i]!= '=') {
      i++;
    }
    if (i == src_len) {
      ctx->decoding_table[63] = 63;
      i = -1;
      continue;
    }
    j = i;
    while (i < src_len && src[i] == '=') {
      i++;
    }
    if (i == src_len) {
      ctx->decoding_table[63] = 63;
      i = -1;
      continue;
    }
    k = i - j;
    x = (unsigned long long) ctx->decoding_table[src[j]];
    y = (unsigned long long) ctx->decoding_table[src[j + 1]];
    x = (x << 6) + y;
    j++;
    y = (unsigned long long) ctx->decoding_table[src[j]];
    x = (x << 6) + y;
    if (i - j == 2) {
      ctx->decoding_table[63] = 63;
      i = -1;
      continue;
    }
    j++;
    y = (unsigned long long) ctx->decoding_table[src[j]];
    x = (x << 6) + y;
    j++;
    y = (unsigned long long) ctx-