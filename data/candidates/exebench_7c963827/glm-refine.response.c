size_t __cdecl scan_ulong(const char *s, unsigned __int64 *l)
{
  unsigned int digit;
  __int64 x = 0;
  size_t n = 0;

  while (1)
  {
    // Subtract ASCII '0' (48) to convert the character to its integer value
    digit = s[n] - '0';
    
    // If the character is not a valid digit (0-9), break out of the loop
    if (digit >= 10)
      break;
      
    // Shift the current value left by one decimal place and add the new digit
    x = (x * 10) + digit;
    ++n;
  }
  
  // Store the final parsed value into the output pointer
  *l = x;
  
  // Return the number of characters successfully parsed
  return n;
}