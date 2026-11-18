void __cdecl vscale(float *dst, const float *src, float scale)
{
  *dst++ = *src++ * scale;
  *dst++ = *src++ * scale;
  *dst   = *src   * scale;
}