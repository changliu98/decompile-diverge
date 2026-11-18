void __cdecl vscale(float *dst, float *src, float scale)
{
  *dst = *src * scale;
  dst[1] = src[1] * scale;
  dst[2] = src[2] * scale;
}