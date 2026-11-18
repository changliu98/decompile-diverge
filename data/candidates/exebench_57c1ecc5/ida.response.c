void __cdecl cftf081(float *a)
{
  float y7i; // [rsp+0h] [rbp-6Ch]
  float y7r; // [rsp+4h] [rbp-68h]
  float y5i; // [rsp+10h] [rbp-5Ch]
  float y5r; // [rsp+14h] [rbp-58h]
  float y3i; // [rsp+20h] [rbp-4Ch]
  float y3r; // [rsp+24h] [rbp-48h]
  float y2i; // [rsp+28h] [rbp-44h]
  float y2r; // [rsp+2Ch] [rbp-40h]
  float y1i; // [rsp+30h] [rbp-3Ch]
  float y1r; // [rsp+34h] [rbp-38h]
  float y0i; // [rsp+38h] [rbp-34h]
  float y0r; // [rsp+3Ch] [rbp-30h]
  float x3i; // [rsp+40h] [rbp-2Ch]
  float x3ia; // [rsp+40h] [rbp-2Ch]
  float x3r; // [rsp+44h] [rbp-28h]
  float x3ra; // [rsp+44h] [rbp-28h]
  float x2i; // [rsp+48h] [rbp-24h]
  float x2ia; // [rsp+48h] [rbp-24h]
  float x2r; // [rsp+4Ch] [rbp-20h]
  float x2ra; // [rsp+4Ch] [rbp-20h]
  float x1i; // [rsp+50h] [rbp-1Ch]
  float x1ia; // [rsp+50h] [rbp-1Ch]
  float x1r; // [rsp+54h] [rbp-18h]
  float x1ra; // [rsp+54h] [rbp-18h]
  float x0i; // [rsp+58h] [rbp-14h]
  float x0ia; // [rsp+58h] [rbp-14h]
  float x0r; // [rsp+5Ch] [rbp-10h]
  float x0ra; // [rsp+5Ch] [rbp-10h]

  x0r = *a + a[8];
  x0i = a[1] + a[9];
  x1r = *a - a[8];
  x1i = a[1] - a[9];
  x2r = a[4] + a[12];
  x2i = a[5] + a[13];
  x3r = a[4] - a[12];
  x3i = a[5] - a[13];
  y0r = x0r + x2r;
  y0i = x0i + x2i;
  y2r = x0r - x2r;
  y2i = x0i - x2i;
  y1r = x1r - x3i;
  y1i = x1i + x3r;
  y3r = x1r + x3i;
  y3i = x1i - x3r;
  x0ra = a[2] + a[10];
  x0ia = a[3] + a[11];
  x1ra = a[2] - a[10];
  x1ia = a[3] - a[11];
  x2ra = a[6] + a[14];
  x2ia = a[7] + a[15];
  x3ra = a[6] - a[14];
  x3ia = a[7] - a[15];
  y5r = 0.70710677 * (float)((float)(x1ra - x3ia) - (float)(x1ia + x3ra));
  y5i = 0.70710677 * (float)((float)(x1ra - x3ia) + (float)(x1ia + x3ra));
  y7r = 0.70710677 * (float)((float)(x1ra + x3ia) - (float)(x1ia - x3ra));
  y7i = 0.70710677 * (float)((float)(x1ra + x3ia) + (float)(x1ia - x3ra));
  a[8] = y1r + y5r;
  a[9] = y1i + y5i;
  a[10] = y1r - y5r;
  a[11] = y1i - y5i;
  a[12] = y3r - y7i;
  a[13] = y3i + y7r;
  a[14] = y3r + y7i;
  a[15] = y3i - y7r;
  *a = y0r + (float)(x0ra + x2ra);
  a[1] = y0i + (float)(x0ia + x2ia);
  a[2] = y0r - (float)(x0ra + x2ra);
  a[3] = y0i - (float)(x0ia + x2ia);
  a[4] = y2r - (float)(x0ia - x2ia);
  a[5] = y2i + (float)(x0ra - x2ra);
  a[6] = y2r + (float)(x0ia - x2ia);
  a[7] = y2i - (float)(x0ra - x2ra);
}