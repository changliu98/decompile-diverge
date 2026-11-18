void conv_sign(int sign_bit, int *value)
{
  if ( *value & sign_bit )
  {
    *value = sign_bit * 2 - *value;
    *value = - *value;
  }
}