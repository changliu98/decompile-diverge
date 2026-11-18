float __cdecl ran2(long *idum)
{
  float v1; // xmm0_4
  int j; // [rsp+10h] [rbp-14h]
  int ja; // [rsp+10h] [rbp-14h]

  if ( *idum <= 0 )
  {
    if ( -*idum >= 1 )
      *idum = -*idum;
    else
      *idum = 1LL;
    ran2_idum2 = *idum;
    for ( j = 39; j >= 0; --j )
    {
      *idum = 40014 * (*idum % 53668) - 12211 * (*idum / 53668);
      if ( *idum < 0 )
        *idum += 2147483563LL;
      if ( j < 32 )
        ran2_iv[j] = *idum;
    }
    ran2_iy = ran2_iv[0];
  }
  *idum = 40014 * (*idum % 53668) - 12211 * (*idum / 53668);
  if ( *idum < 0 )
    *idum += 2147483563LL;
  ran2_idum2 = 40692 * (ran2_idum2 % 52774) - 3791 * (ran2_idum2 / 52774);
  ran2_idum2 += ran2_idum2 < 0 ? 0x7FFFFF07uLL : 0;
  ja = ran2_iy / 67108862;
  ran2_iy = ran2_iv[ja] - ran2_idum2;
  ran2_iv[ja] = *idum;
  if ( ran2_iy < 1 )
    ran2_iy += 2147483562LL;
  v1 = 4.656613057391769e-10 * (double)(int)ran2_iy;
  if ( v1 <= 0.9999997 )
    return 4.656613057391769e-10 * (double)(int)ran2_iy;
  else
    return 0.9999997;
}