void sha1_transform(SHA_CTX *ctx, unsigned char *data) {
  unsigned int t, t1, m;
  unsigned int a, b, c, d, e;
  unsigned int W[80];
  t = 0;
  m = 0;
  for (t = 0; t < 16; t++) {
    W[t] = (data[m] << 24) + (data[m + 1] << 16) + (data[m + 2] << 8) +
           data[m + 3];
    m += 4;
  }
  for (; t < 80; t++) {
    W[t] = (((W[t - 3] ^ W[t - 8] ^ W[t - 14] ^ W[t - 16])) << 1) |
           ((W[t - 3] >> (32 - 1)));
  }
  a = ctx->state[0];
  b = ctx->state[1];
  c = ctx->state[2];
  d = ctx->state[3];
  e = ctx->state[4];
  for (t = 0; t < 20; t++) {
    t1 = (((a) >> (32 - 5)) | ((a) << (32 - (5)))) +
         (((a) & (0xffffffff)) & (b)) + e + ctx->k[0] +
         (((c) & (b)) ^ ((~c) & (d)));
    e = d;
    d = c;
    c = (((b) >> (32 - 30)) | ((b) << (32 - (30))));
    b = a;
    a = t1;
  }
  for (; t < 40; t++) {
    t1 = (((a) >> (32 - 5)) | ((a) << (32 - (5)))) + e + ctx->k[1] +
         (b ^ (c ^ d)) + W[t];
    e = d;
    d = c;
    c = (((b) >> (32 - 30)) | ((b) << (32 - (30))));
    b = a;
    a = t1;
  }
  for (; t < 60; t++) {
    t1 = (((a) >> (32 - 5)) | ((a) << (32 - (5)))) + e + ctx->k[2] +
         ((b ^ c) ^ d) + W[t];
    e = d;
    d = c;
    c = (((b) >> (32 - 30)) | ((b) << (32 - (30))));
    b = a;
    a = t1;
  }
  for (; t < 80; t++) {
    t1 = (((a) >> (32 - 5)) | ((a) << (32 - (5)))) + e + ctx->k[3] +
         (b ^ (c ^ d)) + W[t];
    e = d;
    d = c;
    c = (((b) >> (32 - 30)) | ((b) << (32 - (30))));
    b = a;
    a = t1;
  }
  ctx->state[0] += a;
  ctx->state[1] += b;
  ctx->state[2] += c;
  ctx->state[3] += d;
  ctx->state[4] += e;
}