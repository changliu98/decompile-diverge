void __cdecl itoa(unsigned __int16 value, char *s)
{
  char tmp[16];
  unsigned __int16 len = 0;

  if (value == 0)
  {
    s[0] = '0';
    s[1] = '\0';
    return;
  }

  // Extract digits in reverse order (least significant digit first)
  while (value)
  {
    tmp[len++] = (value % 10) + '0';
    value /= 10;
  }

  // Reverse the extracted digits into the output string
  for (unsigned __int16 i = 0; i < len; ++i)
  {
    s[i] = tmp[len - i - 1];
  }

  s[len] = '\0';
}