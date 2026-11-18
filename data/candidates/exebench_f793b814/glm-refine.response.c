void __cdecl TEA_transform(unsigned int *buf, const unsigned int *in)
{
  unsigned int n;
  unsigned int v0, v1, sum;
  const unsigned int *k = in; // Rename 'in' to 'k' to reflect that it's a key

  sum = 0;
  v0 = buf[0];
  v1 = buf[1];
  n = 16;

  do
  {
    // 1640531527 is 0x9E3779B9, the standard TEA delta value
    sum -= 0x9E3779B9; 
    
    // 16 * b1 is equivalent to b1 << 4
    v0 += (k[1] + (v1 >> 5)) ^ (sum + v1) ^ (k[0] + (v1 << 4));
    
    // 16 * b0 is equivalent to b0 << 4
    v1 += (k[3] + (v0 >> 5)) ^ (sum + v0) ^ (k[2] + (v0 << 4));
    
    --n;
  }
  while ( n );

  buf[0] += v0;
  buf[1] += v1;
}