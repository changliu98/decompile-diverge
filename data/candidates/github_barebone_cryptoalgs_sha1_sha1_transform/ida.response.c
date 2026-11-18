void __cdecl sha1_transform(SHA1_CTX *ctx, const BYTE *data)
{
  WORD m[80]; // [rsp+0h] [rbp-170h]
  WORD t; // [rsp+140h] [rbp-30h]
  WORD j; // [rsp+144h] [rbp-2Ch]
  WORD i; // [rsp+148h] [rbp-28h]
  WORD e; // [rsp+14Ch] [rbp-24h]
  WORD d; // [rsp+150h] [rbp-20h]
  WORD c; // [rsp+154h] [rbp-1Ch]
  WORD b; // [rsp+158h] [rbp-18h]
  WORD a; // [rsp+15Ch] [rbp-14h]
  const BYTE *dataa; // [rsp+160h] [rbp-10h]
  SHA1_CTX *ctxa; // [rsp+168h] [rbp-8h]

  ctxa = ctx;
  dataa = data;
  i = 0;
  j = 0;
  while ( i < 0x10 )
  {
    m[i++] = dataa[j + 3] + (dataa[j + 2] << 8) + (dataa[j + 1] << 16) + (dataa[j] << 24);
    j += 4;
  }
  while ( i < 0x50 )
  {
    m[i] = m[i - 16] ^ m[i - 14] ^ m[i - 8] ^ m[i - 3];
    m[i] = (m[i] >> 31) | (2 * m[i]);
    ++i;
  }
  a = ctxa->state[0];
  b = ctxa->state[1];
  c = ctxa->state[2];
  d = ctxa->state[3];
  e = ctxa->state[4];
  for ( i = 0; i < 0x14; ++i )
  {
    t = m[i] + ctxa->k[0] + e + (d & ~b ^ c & b) + ((a >> 27) | (32 * a));
    e = d;
    d = c;
    c = (b >> 2) | (b << 30);
    b = a;
    a = t;
  }
  while ( i < 0x28 )
  {
    t = m[i] + ctxa->k[1] + e + (d ^ c ^ b) + ((a >> 27) | (32 * a));
    e = d;
    d = c;
    c = (b >> 2) | (b << 30);
    b = a;
    a = t;
    ++i;
  }
  while ( i < 0x3C )
  {
    t = m[i] + ctxa->k[2] + e + (d & c ^ d & b ^ c & b) + ((a >> 27) | (32 * a));
    e = d;
    d = c;
    c = (b >> 2) | (b << 30);
    b = a;
    a = t;
    ++i;
  }
  while ( i < 0x50 )
  {
    t = m[i] + ctxa->k[3] + e + (d ^ c ^ b) + ((a >> 27) | (32 * a));
    e = d;
    d = c;
    c = (b >> 2) | (b << 30);
    b = a;
    a = t;
    ++i;
  }
  ctxa->state[0] += a;
  ctxa->state[1] += b;
  ctxa->state[2] += c;
  ctxa->state[3] += d;
  ctxa->state[4] += e;
}