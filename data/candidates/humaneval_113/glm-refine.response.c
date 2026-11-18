char **__cdecl func0(char **strings, int size)
{
  char **out = (char **)malloc(8LL * size);
  
  for (int i = 0; i < size; ++i)
  {
    unsigned int odd_digit_count = 0;
    
    for (int j = 0; strings[i][j]; ++j)
    {
      char c = strings[i][j];
      // Check if the character is a digit ('0' to '9')
      if (c >= '0' && c <= '9')
      {
        // Convert character to its integer value and check if it's odd
        if ((c - '0') % 2 == 1)
        {
          ++odd_digit_count;
        }
      }
    }
    
    // Allocate 100 bytes for the output string
    out[i] = (char *)malloc(0x64uLL); 
    sprintf(out[i], "the number of odd elements %d in the string %d of the %d input.", 
            odd_digit_count, odd_digit_count, odd_digit_count);
  }
  
  return out;
}