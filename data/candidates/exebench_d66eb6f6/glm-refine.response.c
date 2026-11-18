unsigned int __cdecl bcd2int(unsigned __int8 *s, int slen)
{
  int i;
  int o;

  // A 32-bit unsigned integer can hold a maximum of 10 decimal digits.
  // Because each packed BCD byte holds 2 digits, the maximum length is 5 bytes.
  // If slen > 5, the accumulator would overflow, so the function safely bails out.
  if ( slen > 5 )
    return 0;
    
  o = 0;
  for ( i = 0; i < slen; ++i )
  {
    // Extract the lower nibble (lower decimal digit)
    int lower_digit = s[i] & 0x0F;       // Equivalent to: s[i] % 16
    
    // Extract the upper nibble (upper decimal digit)
    int upper_digit = (s[i] >> 4) & 0x0F; // Equivalent to: s[i] / 16
    
    // Shift the accumulated value by one decimal byte (multiply by 100)
    // and add the newly extracted 2-digit BCD value.
    o = (o * 100) + (upper_digit * 10) + lower_digit;
  }
  
  return o;
}