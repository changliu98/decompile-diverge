int __cdecl i2s_sf_sclkdiv(int div, int *out)
{
  if ( div == 1 )
  {
    *out |= 0x800000u;
    return 0;
  }
  else if ( div == 3 )
  {
    *out |= 0x900000u;
    return 0;
  }
  else if ( div % 2 )
  {
    return -1;
  }
  else if ( div / 2 == 9 || div / 2 == 10 )
  {
    return -1;
  }
  else
  {
    *out |= ((div / 2 - 1) << 20) & 0xF00000;
    return 0;
  }
}