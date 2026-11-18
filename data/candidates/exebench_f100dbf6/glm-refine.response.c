void __cdecl tea_decrypt(uint32_t *v, const uint32_t *k)
{
  uint32_t i;
  uint32_t sum;
  uint32_t v0, v1;

  // Initialize variables
  v0 = v[0];
  v1 = v[1];
  
  // The sum starts at DELTA * 32 (mod 2^32)
  // 2654435769 * 32 = 84941944608
  // 84941944608 mod 2^32 = 3337565984
  sum = 3337565984u; 
  const uint32_t DELTA = 2654435769u;

  // 32 rounds of decryption
  for (i = 0; i < 32; ++i)
  {
    // Decrypt v1
    v1 -= (k[3] + (v0 >> 5)) ^ (sum + v0) ^ (k[2] + (v0 << 4));
    
    // Decrypt v0
    v0 -= (k[1] + (v1 >> 5)) ^ (sum + v1) ^ (k[0] + (v1 << 4));
    
    // Decrement sum
    sum -= DELTA;
  }
  
  // Write back plaintext
  v[0] = v0;
  v[1] = v1;
}