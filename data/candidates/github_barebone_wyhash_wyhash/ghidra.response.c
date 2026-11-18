uint64_t wyhash(void *key,size_t len,uint64_t seed,uint64_t *secret)

{
  ulong uVar1;
  uint64_t uVar2;
  uint64_t uVar3;
  uint64_t see2;
  uint64_t see1;
  size_t i;
  uint64_t b;
  uint64_t a;
  uint8_t *p;
  uint64_t *secret_local;
  uint64_t seed_local;
  size_t len_local;
  void *key_local;
  
  p = key;
  secret_local = secret;
  seed_local = seed;
  len_local = len;
  key_local = key;
  uVar2 = _wymix(seed ^ *secret,secret[1]);
  see2 = uVar2 ^ seed_local;
  seed_local = see2;
  if (len_local < 0x11) {
    if (len_local < 4) {
      if (len_local == 0) {
        a = 0;
      }
      else {
        a = _wyr3(p,len_local);
      }
      b = 0;
    }
    else {
      uVar2 = _wyr4(p);
      uVar3 = _wyr4(p + (len_local >> 3) * 4);
      a = uVar2 << 0x20 | uVar3;
      uVar2 = _wyr4(p + (len_local - 4));
      uVar3 = _wyr4(p + (len_local >> 3) * -4 + (len_local - 4));
      b = uVar2 << 0x20 | uVar3;
    }
  }
  else {
    i = len_local;
    see1 = see2;
    if (0x2f < len_local) {
      do {
        uVar2 = _wyr8(p);
        uVar1 = secret_local[1];
        uVar3 = _wyr8(p + 8);
        seed_local = _wymix(uVar2 ^ uVar1,uVar3 ^ seed_local);
        uVar2 = _wyr8(p + 0x10);
        uVar1 = secret_local[2];
        uVar3 = _wyr8(p + 0x18);
        see1 = _wymix(uVar2 ^ uVar1,uVar3 ^ see1);
        uVar2 = _wyr8(p + 0x20);
        uVar1 = secret_local[3];
        uVar3 = _wyr8(p + 0x28);
        see2 = _wymix(uVar2 ^ uVar1,uVar3 ^ see2);
        p = p + 0x30;
        i = i - 0x30;
      } while (0x2f < i);
      seed_local = see1 ^ see2 ^ seed_local;
    }
    for (; 0x10 < i; i = i - 0x10) {
      uVar2 = _wyr8(p);
      uVar1 = secret_local[1];
      uVar3 = _wyr8(p + 8);
      seed_local = _wymix(uVar2 ^ uVar1,uVar3 ^ seed_local);
      p = p + 0x10;
    }
    a = _wyr8(p + (i - 0x10));
    b = _wyr8(p + (i - 8));
  }
  a = secret_local[1] ^ a;
  b = seed_local ^ b;
  _wymum(&a,&b);
  uVar2 = _wymix(a ^ *secret_local ^ len_local,b ^ secret_local[1]);
  return uVar2;
}