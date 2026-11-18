void __cdecl convertscreenvertex(float *vec, int resolutionx, int resolutiony)
{
  *vec = (float)(*vec - (float)(resolutionx >> 1)) / (float)(resolutionx >> 1);
  vec[1] = (float)((float)(resolutiony >> 1) - vec[1]) / (float)(resolutionx >> 1);
  vec[2] = -1.0;
}