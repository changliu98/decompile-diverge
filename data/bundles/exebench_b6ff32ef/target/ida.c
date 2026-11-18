void __cdecl xformMultiply(float *t, float *s)
{
  float t4; // [rsp+0h] [rbp-1Ch]
  float t2; // [rsp+4h] [rbp-18h]
  float t0; // [rsp+8h] [rbp-14h]

  t0 = (float)(*t * *s) + (float)(t[1] * s[2]);
  t2 = (float)(t[2] * *s) + (float)(t[3] * s[2]);
  t4 = (float)((float)(t[4] * *s) + (float)(t[5] * s[2])) + s[4];
  t[1] = (float)(*t * s[1]) + (float)(t[1] * s[3]);
  t[3] = (float)(t[2] * s[1]) + (float)(t[3] * s[3]);
  t[5] = (float)((float)(t[4] * s[1]) + (float)(t[5] * s[3])) + s[5];
  *t = t0;
  t[2] = t2;
  t[4] = t4;
}