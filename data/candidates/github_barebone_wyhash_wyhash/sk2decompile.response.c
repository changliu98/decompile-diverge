unsigned long long wyhash(const void *key, unsigned long long len,
                          unsigned long long seed,
                          const unsigned long long *secret) {
  const unsigned char *p = (const unsigned char *)key;
  unsigned long long acc, t0, t1, t2;
  unsigned long long acc2, acc3;
  unsigned int n;
  acc = seed ^ secret[0];
  acc = wymix(acc, secret[1]);
  if (len <= 16) {
    if (len >= 4) {
      t0 = wyr4(p) << 32;
      t0 |= wyr4(p + (len >> 3) * 4);
      t1 = wyr4(p + len - 4) << 32;
      t1 |= wyr4(p + len - 4 - (len >> 3) * 4);
    } else if (len >= 1) {
      t0 = wyr3(p, len);
      t1 = 0;
    } else {
      t0 = t1 = 0;
    }
  } else {
    n = len;
    if (len >= 48) {
      acc2 = acc;
      acc3 = acc;
      do {
        t0 = secret[1] ^ wyr8(p);
        acc = wymix(t0, acc ^ wyr8(p + 8));
        t0 = secret[2] ^ wyr8(p + 16);
        acc2 = wymix(t0, acc2 ^ wyr8(p + 24));
        t0 = secret[3] ^ wyr8(p + 32);
        acc3 = wymix(t0, acc3 ^ wyr8(p + 40));
        p += 48;
        n -= 48;
      } while (n >= 48);
      acc ^= acc2 ^ acc3;
    }
    while (n >= 16) {
      t0 = secret[1] ^ wyr8(p);
      acc = wymix(t0, acc ^ wyr8(p + 8));
      p += 16;
      n -= 16;
    }
    t0 = wyr8(p + n - 16);
    t1 = wyr8(p + n - 8);
  }
  t0 ^= secret[1];
  t1 ^= acc;
  wymum(&t0, &t1);
  t2 = len ^ secret[0];
  t2 ^= secret[1];
  acc = wymix(t2, t1);
  return acc;
}