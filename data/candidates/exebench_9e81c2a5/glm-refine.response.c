void __cdecl decipher(uint64_t *v, const uint64_t *k)
{
  uint64_t v0 = v[0];
  uint64_t v1 = v[1];
  
  // 0x1328B7BD67 == 0x9E3779B97F4D715 * 0x1F (31 iterations)
  // 2654435769 == 0x9E3779B9 (Delta value)
  uint64_t sum = 0x1328B7BD67;
  const uint64_t delta = 0x9E3779B9;
  
  for (int i = 0; i < 0x1F; ++i)
  {
    // (v0 >> 5) ^ (16 * v0) is equivalent to (v0 << 4) ^ (v0 >> 5)
    v1 -= (k[(sum >> 11) & 3] + sum) ^ (v0 + ((v0 << 4) ^ (v0 >> 5)));
    sum -= delta;
    v0 -= (k[sum & 3] + sum) ^ (v1 + ((v1 << 4) ^ (v1 >> 5)));
  }
  
  v[0] = v0;
  v[1] = v1;
}