void __cdecl encipher(uint64_t *v, uint64_t *k)
{
  uint64_t v0 = v[0];
  uint64_t v1 = v[1];
  uint64_t sum = 0;
  const uint64_t DELTA = 0x9E3779B9; // 2654435769
  const int ROUNDS = 32;             // 0x1F + 1

  for (int i = 0; i < ROUNDS; ++i)
  {
    // (v1 << 4) ^ (v1 >> 5) is functionally equivalent to (16 * v1) ^ (v1 >> 5)
    v0 += (k[sum & 3] + sum) ^ (v1 + ((v1 << 4) ^ (v1 >> 5)));
    sum += DELTA;
    
    // (sum >> 11) & 3 is equivalent to (sum / 2048) % 4
    v1 += (k[(sum >> 11) & 3] + sum) ^ (v0 + ((v0 << 4) ^ (v0 >> 5)));
  }
  
  v[0] = v0;
  v[1] = v1;
}