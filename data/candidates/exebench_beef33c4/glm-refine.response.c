void __cdecl bn_mul_comba4(unsigned __int64 *r, unsigned __int64 *a, unsigned __int64 *b)
{
  unsigned __int128 c1 = 0;
  unsigned __int128 c2 = 0;
  unsigned __int128 c3 = 0;

  // Round 0: r[0] = a[0]*b[0]
  c1 = (unsigned __int128)a[0] * b[0];
  r[0] = c1;
  c1 >>= 64;

  // Round 1: r[1] = a[0]*b[1] + a[1]*b[0] + c1
  c2 = (unsigned __int128)a[0] * b[1] + c1;
  c3 = c2 >> 64;
  c2 = (unsigned __int128)a[1] * b[0] + (unsigned __int64)c2;
  c3 += c2 >> 64;
  r[1] = c2;
  c1 = c3;

  // Round 2: r[2] = a[0]*b[2] + a[1]*b[1] + a[2]*b[0] + c1
  c2 = (unsigned __int128)a[0] * b[2] + c1;
  c3 = c2 >> 64;
  c2 = (unsigned __int128)a[1] * b[1] + (unsigned __int64)c2;
  c3 += c2 >> 64;
  c2 = (unsigned __int128)a[2] * b[0] + (unsigned __int64)c2;
  c3 += c2 >> 64;
  r[2] = c2;
  c1 = c3;

  // Round 3: r[3] = a[0]*b[3] + a[1]*b[2] + a[2]*b[1] + a[3]*b[0] + c1
  c2 = (unsigned __int128)a[0] * b[3] + c1;
  c3 = c2 >> 64;
  c2 = (unsigned __int128)a[1] * b[2] + (unsigned __int64)c2;
  c3 += c2 >> 64;
  c2 = (unsigned __int128)a[2] * b[1] + (unsigned __int64)c2;
  c3 += c2 >> 64;
  c2 = (unsigned __int128)a[3] * b[0] + (unsigned __int64)c2;
  c3 += c2 >> 64;
  r[3] = c2;
  c1 = c3;

  // Round 4: r[4] = a[1]*b[3] + a[2]*b[2] + a[3]*b[1] + c1
  c2 = (unsigned __int128)a[1] * b[3] + c1;
  c3 = c2 >> 64;
  c2 = (unsigned __int128)a[2] * b[2] + (unsigned __int64)c2;
  c3 += c2 >> 64;
  c2 = (unsigned __int128)a[3] * b[1] + (unsigned __int64)c2;
  c3 += c2 >> 64;
  r[4] = c2;
  c1 = c3;

  // Round 5: r[5] = a[2]*b[3] + a[3]*b[2] + c1
  c2 = (unsigned __int128)a[2] * b[3] + c1;
  c3 = c2 >> 64;
  c2 = (unsigned __int128)a[3] * b[2] + (unsigned __int64)c2;
  c3 += c2 >> 64;
  r[5] = c2;
  c1 = c3;

  // Round 6: r[6] = a[3]*b[3] + c1
  c2 = (unsigned __int128)a[3] * b[3] + c1;
  r[6] = c2;
  c2 >>= 64;

  // Round 7: r[7] = c2
  r[7] = c2;
}