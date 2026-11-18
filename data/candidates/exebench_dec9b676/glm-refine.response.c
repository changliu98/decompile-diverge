void __cdecl mult121665(unsigned char *out, const unsigned char *a)
{
  unsigned int carry = 0;
  unsigned int temp;
  int i;

  // First pass: Multiply 'a' by 121665 and propagate the carry
  for (i = 0; i < 31; ++i)
  {
    temp = carry + 121665 * a[i];
    out[i] = (unsigned char)temp;
    carry = temp >> 8;
  }

  // Process the 32nd byte, masking to 7 bits (indicating a 255-bit integer)
  temp = carry + 121665 * a[31];
  out[31] = temp & 0x7F;

  // Calculate the overflow to carry back (modular reduction by 2^255 - 19)
  carry = 19 * (temp >> 7);

  // Second pass: Add the reduction overflow back into the result
  for (i = 0; i < 31; ++i)
  {
    temp = carry + out[i];
    out[i] = (unsigned char)temp;
    carry = temp >> 8;
  }

  // Add the remaining carry to the most significant byte
  out[31] += carry;
}