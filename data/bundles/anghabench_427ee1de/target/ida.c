int __cdecl ctsxs(unsigned int x, int scale, unsigned int *vscrp)
{
  int v3; // eax
  unsigned __int64 mant; // [rsp+4h] [rbp-20h]
  int manta; // [rsp+4h] [rbp-20h]

  HIDWORD(mant) = (unsigned __int8)(x >> 23);
  LODWORD(mant) = x & 0x7FFFFF;
  if ( mant > 0xFF00000000LL )
    return 0;
  HIDWORD(mant) = scale + HIDWORD(mant) - 127;
  if ( (mant & 0x8000000000000000LL) != 0LL )
    return 0;
  if ( SHIDWORD(mant) < 31 )
  {
    manta = (int)(((unsigned int)mant | 0x800000) << 7) >> (30 - BYTE4(mant));
    if ( (x & 0x80000000) == 0 )
      return manta;
    else
      return -manta;
  }
  else
  {
    if ( (scale << 23) + x != -822083584 )
      *vscrp |= VSCR_SAT;
    v3 = 0x7FFFFFFF;
    if ( (x & 0x80000000) != 0 )
      return 0x80000000;
    return v3;
  }
}