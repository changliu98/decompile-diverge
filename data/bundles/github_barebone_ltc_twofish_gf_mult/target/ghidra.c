ulong32 gf_mult(ulong32 a,ulong32 b,ulong32 p)

{
  ulong32 P [2];
  ulong32 B [2];
  ulong32 result;
  ulong32 p_local;
  ulong32 b_local;
  ulong32 a_local;
  
  P[1] = p;
  B[1] = b;
  B[0] = 0;
  P[0] = 0;
  B[1] = P[b >> 7] ^ b << 1;
  B[1] = P[B[1] >> 7] ^ B[1] << 1;
  B[1] = P[B[1] >> 7] ^ B[1] << 1;
  B[1] = P[B[1] >> 7] ^ B[1] << 1;
  B[1] = P[B[1] >> 7] ^ B[1] << 1;
  B[1] = P[B[1] >> 7] ^ B[1] << 1;
  B[1] = P[B[1] >> 7] ^ B[1] << 1;
  return B[a >> 7 & 1] ^
         B[a >> 6 & 1] ^
         B[a >> 5 & 1] ^ B[a >> 4 & 1] ^ B[a >> 3 & 1] ^ B[a >> 2 & 1] ^ B[a >> 1 & 1] ^ B[a & 1];
}