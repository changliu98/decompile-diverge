0x7FFFFF20

int32_t __cdecl readUnicode(const char *in, int *bit_no_p, int len)
{
  int sign_bit;
  int value;
  int idx;

  // Read the 5-bit step code to determine the unicode category
  idx = getStepCodeIdx(in, len, bit_no_p, 5);
  
  if (idx == 99)
    return E_INVALID_DATA;
    
  if (idx == 5)
    return getStepCodeIdx(in, len, bit_no_p, 4) + E_BASE_OFFSET;
    
  if (idx < 0)
    return 0;

  // Read the sign bit (if within bounds)
  if (*bit_no_p >= len)
    sign_bit = 0;
  else
    sign_bit = readBit(in, *bit_no_p);
    
  ++*bit_no_p;

  // Check if there are enough bits left to read the variable-length value
  if (uni_bit_len[idx] + *bit_no_p - 1 >= len)
    return E_INVALID_DATA;

  // Extract the value and apply the category-specific base offset
  value = getNumFromBits(in, len, *bit_no_p, uni_bit_len[idx]) + uni_adder[idx];
  
  // Advance the bit pointer by the length of the value
  *bit_no_p += uni_bit_len[idx];

  // Return positive or negative value based on the sign bit
  if (sign_bit)
    return -value;
  else
    return value;
}