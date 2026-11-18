void __cdecl cftf040(float *a)
{
  float x3i; // [rsp+0h] [rbp-28h]
  float x3r; // [rsp+4h] [rbp-24h]
  float x2i; // [rsp+8h] [rbp-20h]
  float x2r; // [rsp+Ch] [rbp-1Ch]
  float x1i; // [rsp+10h] [rbp-18h]
  float x1r; // [rsp+14h] [rbp-14h]
  float x0i; // [rsp+18h] [rbp-10h]
  float x0r; // [rsp+1Ch] [rbp-Ch]

  x0r = *a + a[4];
  x0i = a[1] + a[5];
  x1r = *a - a[4];
  x1i = a[1] - a[5];
  x2r = a[2] + a[6];
  x2i = a[3] + a[7];
  x3r = a[2] - a[6];
  x3i = a[3] - a[7];
  *a = x0r + x2r;
  a[1] = x0i + x2i;
  a[2] = x1r - x3i;
  a[3] = x1i + x3r;
  a[4] = x0r - x2r;
  a[5] = x0i - x2i;
  a[6] = x1r + x3i;
  a[7] = x1i - x3r;
}