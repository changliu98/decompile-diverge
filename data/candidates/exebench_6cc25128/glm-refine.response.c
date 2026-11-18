define TEA_DELTA 0x9E3779B9ULL

void __cdecl encrypt(uint64_t *v, const uint64_t *k)
{
  uint64_t v0 = v[0];
  uint64_t v1 = v[1];
  uint64_t sum = 0;

  // 0x20 (32) is the standard number of rounds for XTEA/TEA
  for (int i = 0; i < 32; ++i)
  {
    sum += TEA_DELTA;
    
    // Standard XTEA round function (using 64-bit integers instead of standard 32-bit)
    v0 += (k[1] + (v1 >> 5)) ^ (sum + v1) ^ (k[0] + (v1 << 4));
    v1 += (k[3] + (v0 >> 5)) ^ (sum + v0) ^ (k[2] + (v0 << 4));
  }

  v[0] = v0;
  v[1] = v1;
}