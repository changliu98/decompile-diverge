void __cdecl r2d(double *ra, double *dec, int *ih, double *am, char *isgn, int *id, double *amin)
{
  float v7; // xmm0_4
  float v8; // xmm0_4
  float v9; // xmm0_4
  float hours; // [rsp+4h] [rbp-40h]

  v7 = *ra / 0.017453292 / 15.0;
  for ( hours = v7; hours > 24.0; hours = v8 )
    v8 = hours - 24.0;
  *ih = (int)hours;
  *am = (float)(hours - (float)(int)hours) * 60.0;
  *am = *am + 0.000001;
  if ( *am >= 60.0 )
  {
    *am = *am - 60.0;
    ++*ih;
  }
  if ( *ih >= 24 )
    *ih -= 24;
  if ( *dec >= 0.0 )
  {
    *isgn = 43;
  }
  else
  {
    *isgn = 45;
    *(_QWORD *)dec ^= 0x8000000000000000LL;
  }
  v9 = *dec / 0.017453292;
  *id = (int)v9;
  *amin = (float)(v9 - (float)*id) * 60.0;
}