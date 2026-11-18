float __cdecl avg12(float *BufX, float *BufY, size_t Cnt)
{
  float Sum = 0.0;
  float Divisor;

  // Calculate the sum of BufY[n] * BufX[n]^2
  for ( size_t n = 0; n < Cnt; ++n )
    Sum += BufY[n] * BufX[n] * BufX[n];

  // Equivalent to: if (Cnt >= 0) Divisor = (float)Cnt; else Divisor = (float)(2 * ((Cnt / 2) + (Cnt % 2)));
  // Since Cnt is an unsigned 64-bit integer, it is always >= 0.
  if ( (Cnt & 0x8000000000000000LL) == 0LL )
    Divisor = (float)Cnt;
  else
    Divisor = (float)(int)((Cnt >> 1) | (Cnt & 1)) * 2.0f;

  return Sum / Divisor;
}