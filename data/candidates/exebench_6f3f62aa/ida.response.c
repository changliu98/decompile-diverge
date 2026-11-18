float __cdecl ran1(long *idum)
{
  float v1; // xmm0_4
  int j; // [rsp+10h] [rbp-14h]
  int ja; // [rsp+10h] [rbp-14h]

  if ( *idum <= 0 || !ran1_iy )
  {
    if ( -*idum >= 1 )
      *idum = -*idum;
    else
      *idum = 1LL;
    for ( j = 39; j >= 0; --j )
    {
      *idum = 16807 * (*idum % 127773) - 2836 * (*idum / 127773);
      if ( *idum < 0 )
        *idum += 0x7FFFFFFFLL;
      if ( j < 32 )
        ran1_iv[j] = *idum;
    }
    ran1_iy = ran1_iv[0];
  }
  *idum = 16807 * (*idum % 127773) - 2836 * (*idum / 127773);
  if ( *idum < 0 )
    *idum += 0x7FFFFFFFLL;
  ja = ran1_iy / 0x4000000;
  ran1_iy = ran1_iv[ja];
  ran1_iv[ja] = *idum;
  v1 = 4.656612875245797e-10 * (double)(int)ran1_iy;
  if ( v1 <= 0.99999988 )
    return 4.656612875245797e-10 * (double)(int)ran1_iy;
  else
    return 0.99999988;
}