uint64_t __cdecl wyhash(const void *key, size_t len, uint64_t seed, const uint64_t *secret)
{
  uint64_t seeda, see1, see2, a, b;
  const uint8_t *p = (const uint8_t *)key;
  size_t i = len;

  seeda = seed ^ wymix(secret[0] ^ seed, secret[1]);

  if (len > 16)
  {
    if (len >= 48)
    {
      see1 = seeda;
      see2 = seeda;
      do
      {
        seeda = wymix(secret[1] ^ wyr8(p),     seeda ^ wyr8(p + 8));
        see1  = wymix(secret[2] ^ wyr8(p + 16), see1 ^ wyr8(p + 24));
        see2  = wymix(secret[3] ^ wyr8(p + 32), see2 ^ wyr8(p + 40));
        p += 48;
        i -= 48;
      }
      while (i >= 48);

      seeda ^= see1 ^ see2;
    }

    while (i > 16)
    {
      seeda = wymix(secret[1] ^ wyr8(p), seeda ^ wyr8(p + 8));
      i -= 16;
      p += 16;
    }

    a = wyr8(p + i - 16);
    b = wyr8(p + i - 8);
  }
  else if (len < 4)
  {
    if (len)
    {
      a = wyr3(p, len);
      b = 0;
    }
    else
    {
      a = 0;
      b = 0;
    }
  }
  else
  {
    a = ((uint64_t)wyr4(p)) << 32 | wyr4(p + 4 * (len >> 3));
    b = ((uint64_t)wyr4(p + len - 4)) << 32 | wyr4(p + len - 4 - 4 * (len >> 3));
  }

  a ^= secret[1];
  b ^= seeda;
  wymum(&a, &b);

  return wymix(len ^ secret[0] ^ a, secret[1] ^ b);
}