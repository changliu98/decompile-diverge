define MCLKDIV_MASK           0x1F000000

int __cdecl i2s_sf_mclkdiv(int div, int *out)
{
  // Handle special cases for odd divisors
  switch ( div )
  {
    case 1:
      *out |= 0x14000000u;
      return I2S_SF_MCLKDIV_SUCCESS;
    case 3:
      *out |= 0x13000000u;
      return I2S_SF_MCLKDIV_SUCCESS;
    case 5:
      *out |= 0x12000000u;
      return I2S_SF_MCLKDIV_SUCCESS;
    case 14:
      *out |= 0x0E000000u;
      return I2S_SF_MCLKDIV_SUCCESS;
  }

  // Reject unsupported odd divisors
  if ( div % 2 != 0 )
  {
    return I2S_SF_MCLKDIV_ERROR;
  }

  int half_div = div / 2;

  // Reject unsupported even divisors
  if ( half_div == 15 || half_div == 19 || half_div == 20 || half_div == 21 )
  {
    return I2S_SF_MCLKDIV_ERROR;
  }

  // Calculate and apply the register field for supported even divisors
  *out |= ((half_div - 1) << 24) & MCLKDIV_MASK;
  
  return I2S_SF_MCLKDIV_SUCCESS;
}