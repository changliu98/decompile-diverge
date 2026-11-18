void __cdecl af_filter_bilinear(const float *a, const float *b, float *k, float fs_0, float *coef)
{
  float v5; // xmm0_4
  float v6; // xmm0_4
  float v7; // xmm0_4
  float v8; // xmm0_4
  float v9; // xmm0_4
  float v10; // xmm0_4
  float bd; // [rsp+0h] [rbp-30h]
  float ad; // [rsp+4h] [rbp-2Ch]

  v5 = 4.0 * a[2] * fs_0 * fs_0 + 2.0 * a[1] * fs_0 + *a;
  ad = v5;
  v6 = 4.0 * b[2] * fs_0 * fs_0 + 2.0 * b[1] * fs_0 + *b;
  bd = v6;
  *k = (float)(ad / v6) * *k;
  v7 = (*b + *b - 8.0 * b[2] * fs_0 * fs_0) / v6;
  *coef = v7;
  v8 = (4.0 * b[2] * fs_0 * fs_0 - 2.0 * b[1] * fs_0 + *b) / bd;
  coef[1] = v8;
  v9 = (*a + *a - 8.0 * a[2] * fs_0 * fs_0) / ad;
  coef[2] = v9;
  v10 = (4.0 * a[2] * fs_0 * fs_0 - 2.0 * a[1] * fs_0 + *a) / ad;
  coef[3] = v10;
}