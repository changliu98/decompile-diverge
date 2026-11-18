int __cdecl libbf_is_composed_poweroftwo(unsigned int number, int *shift1, int *shift2)
{
  int bit_index = 0;
  int set_bits_count = 0;

  if (!number)
    return 0;

  if (shift1)
    *shift1 = 0;
  if (shift2)
    *shift2 = 0;

  while (number)
  {
    if (number & 1)
    {
      ++set_bits_count;
      
      if (set_bits_count == 1)
      {
        if (shift1)
          *shift1 = bit_index;
      }
      else if (set_bits_count == 2)
      {
        if (shift2)
          *shift2 = bit_index;
      }
      else // More than 2 bits are set
      {
        return 0;
      }
    }
    
    ++bit_index;
    number >>= 1;
  }

  return 1;
}