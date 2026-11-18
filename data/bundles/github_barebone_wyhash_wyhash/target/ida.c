uint64_t __cdecl wyhash(const void *key, size_t len, uint64_t seed, const uint64_t *secret)
{
  uint64_t v4; // rax
  uint64_t v5; // rax
  uint64_t v6; // rax
  uint64_t v7; // rax
  uint64_t v9; // [rsp+0h] [rbp-80h]
  uint64_t A; // [rsp+8h] [rbp-78h]
  uint64_t v11; // [rsp+10h] [rbp-70h]
  uint64_t v12; // [rsp+18h] [rbp-68h]
  uint64_t v13; // [rsp+20h] [rbp-60h]
  uint64_t v14; // [rsp+28h] [rbp-58h]
  uint64_t see2; // [rsp+30h] [rbp-50h]
  uint64_t see1; // [rsp+38h] [rbp-48h]
  size_t i; // [rsp+40h] [rbp-40h]
  uint64_t b; // [rsp+48h] [rbp-38h] BYREF
  uint64_t a; // [rsp+50h] [rbp-30h] BYREF
  const uint8_t *p; // [rsp+58h] [rbp-28h]
  const uint64_t *secreta; // [rsp+60h] [rbp-20h]
  uint64_t seeda; // [rsp+68h] [rbp-18h]
  size_t lena; // [rsp+70h] [rbp-10h]
  const void *keya; // [rsp+78h] [rbp-8h]

  keya = key;
  lena = len;
  secreta = secret;
  p = (const uint8_t *)key;
  seeda = seed ^ wymix(*secret ^ seed, secret[1]);
  if ( len > 0x10 )
  {
    i = lena;
    if ( lena >= 0x30 )
    {
      see1 = seeda;
      see2 = seeda;
      do
      {
        A = secreta[1] ^ wyr8(p);
        v4 = wyr8(p + 8);
        seeda = wymix(A, seeda ^ v4);
        v11 = secreta[2] ^ wyr8(p + 16);
        v5 = wyr8(p + 24);
        see1 = wymix(v11, see1 ^ v5);
        v12 = secreta[3] ^ wyr8(p + 32);
        v6 = wyr8(p + 40);
        see2 = wymix(v12, see2 ^ v6);
        p += 48;
        i -= 48LL;
      }
      while ( i >= 0x30 );
      seeda ^= see2 ^ see1;
    }
    while ( i > 0x10 )
    {
      v9 = secreta[1] ^ wyr8(p);
      v7 = wyr8(p + 8);
      seeda = wymix(v9, seeda ^ v7);
      i -= 16LL;
      p += 16;
    }
    a = wyr8(&p[i - 16]);
    b = wyr8(&p[i - 8]);
  }
  else if ( lena < 4 )
  {
    if ( lena )
    {
      a = wyr3(p, lena);
      b = 0LL;
    }
    else
    {
      b = 0LL;
      a = 0LL;
    }
  }
  else
  {
    v13 = wyr4(p) << 32;
    a = wyr4(&p[4 * (lena >> 3)]) | v13;
    v14 = wyr4(&p[lena - 4]) << 32;
    b = wyr4(&p[lena - 4 + -4 * (lena >> 3)]) | v14;
  }
  a ^= secreta[1];
  b ^= seeda;
  wymum(&a, &b);
  return wymix(lena ^ *secreta ^ a, secreta[1] ^ b);
}