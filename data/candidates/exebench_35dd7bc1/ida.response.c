int __cdecl i2s_sf_mclkdiv(int div, int *out)
{
  int v3; // [rsp+1Ch] [rbp-4h]

  switch ( div )
  {
    case 1:
      *out |= 0x14000000u;
      v3 = 0;
      break;
    case 3:
      *out |= 0x13000000u;
      v3 = 0;
      break;
    case 5:
      *out |= 0x12000000u;
      v3 = 0;
      break;
    case 14:
      *out |= 0xE000000u;
      v3 = 0;
      break;
    default:
      if ( div % 2 )
      {
        v3 = -1;
      }
      else if ( div / 2 == 21 || div / 2 == 20 || div / 2 == 19 || div / 2 == 15 )
      {
        v3 = -1;
      }
      else
      {
        *out |= ((div / 2 - 1) << 24) & 0x1F000000;
        v3 = 0;
      }
      break;
  }
  return v3;
}