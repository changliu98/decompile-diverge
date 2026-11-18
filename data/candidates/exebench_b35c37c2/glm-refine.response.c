void __cdecl itox(unsigned __int16 value, char *s)
{
  char tmp[16];
  unsigned __int16 index = 0;

  if (value)
  {
    // Convert value to hex string in reverse order
    while (value)
    {
      unsigned __int16 digit = value % 16;
      
      if (digit >= 0xA)
        tmp[index] = digit - 10 + 'a'; // Lowercase a-f
      else
        tmp[index] = digit + '0';      // Digits 0-9
        
      index++;
      value /= 16;
    }

    // Reverse the string into the output buffer
    unsigned __int16 length = index;
    while (index)
    {
      index--;
      s[length - 1 - index] = tmp[index];
    }
    
    s[length] = '\0';
  }
  else
  {
    // Handle the zero case
    s[0] = '0';
    s[1] = '\0';
  }
}