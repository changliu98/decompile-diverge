void sha1_transform(SHA1_CTX *ctx,BYTE *data)

{
  int iVar1;
  ulong uVar2;
  WORD m [80];
  WORD t;
  WORD j;
  WORD i;
  WORD e;
  WORD d;
  WORD c;
  WORD b;
  WORD a;
  BYTE *data_local;
  SHA1_CTX *ctx_local;
  
  j = 0;
  for (i = 0; i < 0x10; i = i + 1) {
    m[i] = (uint)data[j] * 0x1000000 + (uint)data[j + 1] * 0x10000 + (uint)data[j + 2] * 0x100 +
           (uint)data[j + 3];
    j = j + 4;
  }
  for (; i < 0x50; i = i + 1) {
    m[i] = m[i - 3] ^ m[i - 8] ^ m[i - 0xe] ^ m[i - 0x10];
    m[i] = m[i] << 1 | m[i] >> 0x1f;
  }
  b = ctx->state[1];
  c = ctx->state[2];
  d = ctx->state[3];
  e = ctx->state[4];
  a = ctx->state[0];
  for (i = 0; i < 0x14; i = i + 1) {
    iVar1 = (a << 5 | a >> 0x1b) + (b & c ^ (b ^ 0xffffffff) & d) + e;
    uVar2 = (ulong)i;
    e = d;
    d = c;
    c = b << 0x1e | b >> 2;
    b = a;
    a = iVar1 + ctx->k[0] + m[uVar2];
  }
  for (; i < 0x28; i = i + 1) {
    iVar1 = (a << 5 | a >> 0x1b) + (b ^ c ^ d) + e;
    uVar2 = (ulong)i;
    e = d;
    d = c;
    c = b << 0x1e | b >> 2;
    b = a;
    a = iVar1 + ctx->k[1] + m[uVar2];
  }
  for (; i < 0x3c; i = i + 1) {
    iVar1 = (a << 5 | a >> 0x1b) + (b & c ^ b & d ^ c & d) + e;
    uVar2 = (ulong)i;
    e = d;
    d = c;
    c = b << 0x1e | b >> 2;
    b = a;
    a = iVar1 + ctx->k[2] + m[uVar2];
  }
  for (; i < 0x50; i = i + 1) {
    iVar1 = (a << 5 | a >> 0x1b) + (b ^ c ^ d) + e;
    uVar2 = (ulong)i;
    e = d;
    d = c;
    c = b << 0x1e | b >> 2;
    b = a;
    a = iVar1 + ctx->k[3] + m[uVar2];
  }
  ctx->state[0] = a + ctx->state[0];
  ctx->state[1] = b + ctx->state[1];
  ctx->state[2] = c + ctx->state[2];
  ctx->state[3] = d + ctx->state[3];
  ctx->state[4] = e + ctx->state[4];
  return;
}