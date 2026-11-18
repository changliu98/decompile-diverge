void __cdecl sha1_transform(SHA1_CTX *ctx, const BYTE *data)
{
  WORD m[80];
  WORD t;
  WORD offset;
  WORD i;
  WORD e, d, c, b, a;

  // Initialize the first 16 words in the message schedule (big-endian)
  for (i = 0, offset = 0; i < 16; i++, offset += 4)
  {
    m[i] = (data[offset] << 24) | (data[offset + 1] << 16) | 
           (data[offset + 2] << 8) | data[offset + 3];
  }

  // Extend the message schedule to 80 words
  for (i = 16; i < 80; i++)
  {
    m[i] = m[i - 16] ^ m[i - 14] ^ m[i - 8] ^ m[i - 3];
    m[i] = (m[i] << 1) | (m[i] >> 31); // Left rotate by 1
  }

  // Initialize hash value for this chunk
  a = ctx->state[0];
  b = ctx->state[1];
  c = ctx->state[2];
  d = ctx->state[3];
  e = ctx->state[4];

  // Round 1 (0-19): f = (b & c) | (~b & d)
  for (i = 0; i < 20; i++)
  {
    t = m[i] + ctx->k[0] + e + ((b & c) ^ (~b & d)) + ((a << 5) | (a >> 27));
    e = d;
    d = c;
    c = (b << 30) | (b >> 2);
    b = a;
    a = t;
  }

  // Round 2 (20-39): f = b ^ c ^ d
  for (i = 20; i < 40; i++)
  {
    t = m[i] + ctx->k[1] + e + (b ^ c ^ d) + ((a << 5) | (a >> 27));
    e = d;
    d = c;
    c = (b << 30) | (b >> 2);
    b = a;
    a = t;
  }

  // Round 3 (40-59): f = (b & c) | (b & d) | (c & d)
  for (i = 40; i < 60; i++)
  {
    t = m[i] + ctx->k[2] + e + ((b & c) ^ (b & d) ^ (c & d)) + ((a << 5) | (a >> 27));
    e = d;
    d = c;
    c = (b << 30) | (b >> 2);
    b = a;
    a = t;
  }

  // Round 4 (60-79): f = b ^ c ^ d
  for (i = 60; i < 80; i++)
  {
    t = m[i] + ctx->k[3] + e + (b ^ c ^ d) + ((a << 5) | (a >> 27));
    e = d;
    d = c;
    c = (b << 30) | (b >> 2);
    b = a;
    a = t;
  }

  // Add this chunk's hash to the running state
  ctx->state[0] += a;
  ctx->state[1] += b;
  ctx->state[2] += c;
  ctx->state[3] += d;
  ctx->state[4] += e;
}