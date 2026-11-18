bool hex_to_int(const char *s, int *x)
{
  *x = 0;
  
  for (int i = 0; i < 8; ++i)
  {
    char c = s[i];
    
    if (c >= '0' && c <= '9')
    {
      *x = *x * 16 + (c - '0');
    }
    else if (c >= 'a' && c <= 'f')
    {
      *x = *x * 16 + (c - 'a' + 10);
    }
    else
    {
      return false; // Invalid hex character
    }
  }
  
  return true;
}