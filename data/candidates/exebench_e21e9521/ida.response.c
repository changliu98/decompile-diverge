float __cdecl avg12(float *BufX, float *BufY, size_t Cnt)
{
  float v4; // [rsp+4h] [rbp-2Ch]
  size_t n; // [rsp+8h] [rbp-28h]
  float Avg; // [rsp+14h] [rbp-1Ch]

  Avg = 0.0;
  for ( n = 0LL; n < Cnt; ++n )
    Avg = (float)((float)(BufY[n] * BufX[n]) * BufX[n]) + Avg;
  v4 = (float)(int)((Cnt >> 1) | Cnt & 1) + (float)(int)((Cnt >> 1) | Cnt & 1);
  if ( (Cnt & 0x8000000000000000LL) == 0LL )
    v4 = (float)(int)Cnt;
  return Avg / v4;
}