void __cdecl mdct_butterfly_8(float *x)
{
  float r3; // [rsp+0h] [rbp-18h]
  float r2; // [rsp+4h] [rbp-14h]
  float r2a; // [rsp+4h] [rbp-14h]
  float r1; // [rsp+8h] [rbp-10h]
  float r1a; // [rsp+8h] [rbp-10h]
  float r0; // [rsp+Ch] [rbp-Ch]
  float r0a; // [rsp+Ch] [rbp-Ch]
  float r0b; // [rsp+Ch] [rbp-Ch]

  r0 = x[6] + x[2];
  r1 = x[6] - x[2];
  r2 = x[4] + *x;
  r3 = x[4] - *x;
  x[6] = r0 + r2;
  x[4] = r0 - r2;
  r0a = x[5] - x[1];
  r2a = x[7] - x[3];
  *x = r1 + r0a;
  x[2] = r1 - r0a;
  r0b = x[5] + x[1];
  r1a = x[7] + x[3];
  x[3] = r2a + r3;
  x[1] = r2a - r3;
  x[7] = r1a + r0b;
  x[5] = r1a - r0b;
}