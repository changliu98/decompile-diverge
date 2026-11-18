ulong32 __cdecl gf_mult(ulong32 a, ulong32 b, ulong32 p)
{
  ulong32 P[2]; // [rsp+0h] [rbp-20h]
  ulong32 B[2]; // [rsp+8h] [rbp-18h]
  ulong32 result; // [rsp+10h] [rbp-10h]
  ulong32 pa; // [rsp+14h] [rbp-Ch]
  ulong32 ba; // [rsp+18h] [rbp-8h]
  ulong32 aa; // [rsp+1Ch] [rbp-4h]

  aa = a;
  ba = b;
  pa = p;
  P[1] = p;
  B[1] = b;
  B[0] = 0;
  P[0] = 0;
  result = 0;
  result = B[a & 1];
  aa = a >> 1;
  B[1] = (2 * b) ^ P[b >> 7];
  result ^= B[(a & 2) != 0];
  aa = a >> 2;
  B[1] = (2 * B[1]) ^ P[B[1] >> 7];
  result ^= B[(a & 4) != 0];
  aa = a >> 3;
  B[1] = (2 * B[1]) ^ P[B[1] >> 7];
  result ^= B[(a & 8) != 0];
  aa = a >> 4;
  B[1] = (2 * B[1]) ^ P[B[1] >> 7];
  result ^= B[(a & 0x10) != 0];
  aa = a >> 5;
  B[1] = (2 * B[1]) ^ P[B[1] >> 7];
  result ^= B[(a & 0x20) != 0];
  aa = a >> 6;
  B[1] = (2 * B[1]) ^ P[B[1] >> 7];
  result ^= B[(a & 0x40) != 0];
  aa = a >> 7;
  B[1] = (2 * B[1]) ^ P[B[1] >> 7];
  return result ^ B[(a & 0x80) != 0];
}