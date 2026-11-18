void int2compl(int sign_bit, int *value)
{
  if ( *value & sign_bit )
  {
    *value = sign_bit * 2 - *value;
    *value = - *value;
  }
}