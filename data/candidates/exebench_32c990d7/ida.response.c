void __cdecl conv_sign(unsigned int sign_bit, int *value)
{
  if ( (sign_bit & *value) != 0 )
  {
    *value = 2 * sign_bit - *value;
    *value = -*value;
  }
}