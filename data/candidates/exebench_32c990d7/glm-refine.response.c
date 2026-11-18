void __cdecl conv_sign(unsigned int sign_bit, int *value)
{
  int val = *value;

  // Check if the sign_bit is set in the value
  if ((sign_bit & val) != 0)
  {
    // If the bit is set, treat the value as a negative number 
    // encoded in a biased format and convert it to standard two's complement.
    val = -(2 * sign_bit - val);
    *value = val;
  }
}