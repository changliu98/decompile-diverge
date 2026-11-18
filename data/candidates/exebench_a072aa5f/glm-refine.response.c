define TEA_SUM_INIT 0xC6EF3720ULL

void __cdecl decrypt(unsigned __int64 *v, unsigned __int64 *k)
{
  unsigned __int64 i;
  unsigned __int64 sum;
  unsigned __int64 v0;
  unsigned __int64 v1;

  // Load the 64-bit block halves
  v0 = v[0];
  v1 = v[1];
  
  sum = TEA_SUM_INIT;
  
  // 32 rounds of decryption
  for ( i = 0; i < 32; ++i )
  {
    // The original code uses 64-bit arithmetic, but the structure is 
    // a standard TEA decrypt round operating on 32-bit halves.
    v1 -= (k[3] + (v0 >> 5)) ^ (sum + v0) ^ (k[2] + (v0 << 4));
    v0 -= (k[1] + (v1 >> 5)) ^ (sum + v1) ^ (k[0] + (v1 << 4));
    
    // Reverse the sum addition (equivalent to sum -= TEA_DELTA)
    sum -= TEA_DELTA;
  }
  
  // Store the decrypted block halves
  v[0] = v0;
  v[1] = v1;
}