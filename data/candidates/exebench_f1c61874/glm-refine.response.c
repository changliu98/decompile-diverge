void __cdecl squeeze(unsigned int *a)
{
  unsigned int carry = 0;

  // First pass: add the carry chain to the first 31 elements
  for (unsigned int j = 0; j < 0x1F; ++j)
  {
    unsigned int sum = carry + a[j];
    a[j] = (unsigned char)sum;
    carry = sum >> 8;
  }

  // Process the 32nd element (index 31) and extract the overflow bit
  unsigned int sum = carry + a[31];
  a[31] = sum & 0x7F;
  carry = 19 * (sum >> 7);

  // Second pass: propagate the overflow (multiplied by 19) back into the array
  for (unsigned int j = 0; j < 0x1F; ++j)
  {
    unsigned int sum2 = carry + a[j];
    a[j] = (unsigned char)sum2;
    carry = sum2 >> 8;
  }

  // Add the final remaining carry to the 32nd element
  a[31] += carry;
}