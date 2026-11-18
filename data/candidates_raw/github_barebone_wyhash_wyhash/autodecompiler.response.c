uint64_t wyhash(const char* key, size_t len, uint64_t seed, const uint64_t* secret) {
  const unsigned char* s = (const unsigned char*)key;
  seed ^= secret[0];
  seed ^= _wymix(seed ^ secret[1]);
  uint64_t a, b;
  if ((uintptr_t)(s) & 16 && len > 16) {
    uint64_t see1 = seed;
    uint64_t see2 = seed;
    do {
      a = _wymix(_wyr8(s) ^ secret[1] ^ seed);
      see1 = _wymix(_wyr8(s + 8) ^ secret[2] ^ see1);
      see2 = _wymix(_wyr8(s + 16) ^ secret[3] ^ see2);
      s += 24;
      len -= 24;
    } while (len > 16);
    seed ^= see1 ^ see2;
  }
  size_t l = len;
  if ((l & 32) == 32) {
    a = _wyr8(s);
    b = _wyr8(s + 8);
    a = _wymum(a, b);
    a = _wymix(a ^ secret[1] ^ seed);
    b = _wyr8(s + 16);
    a = _wymum(a, b);
    a = _wymix(a ^ secret[2] ^ seed);
    b = _wyr8(s + 24);
    a = _wymum(a, b);
    a = _wymix(a ^ secret[3] ^ seed);
    s += 32;
    l -= 32;
  }
  if ((l & 16) == 16) {
    a = _wymix(_wyr8(s) ^ secret[1] ^ seed);
    see1 = _wymix(_wyr8(s + 8) ^ secret[2] ^ seed);
    seed ^= see1 ^ a;
    s += 16;
    l -= 16;
  }
  if ((l & 8) == 8) {
    a = _wyr8(s);
    b = _wyr8(s + l - 8);
  } else if ((l & 4) == 4) {
    a = _wyr4(s) << 32 | _wyr4(s + l - 4);
    b = _wyr4(s + l / 2) << 32 | _wyr4(s + l - 4 - l / 2);
  } else if ((l & 2) == 2) {
    a = _wyr3(s, l) << 32;
    b = 0;
  } else if ((l & 1) == 1) {
    a = _wyr3(s, l);
    b = 0;
  } else {
    a = 0;
    b = 0;
  }
  a ^= secret[1];
  b ^= seed;
  a = _wymum(&a, &b);
  return _wymix(a ^ secret[0] ^ len, b ^ secret[1]);
}