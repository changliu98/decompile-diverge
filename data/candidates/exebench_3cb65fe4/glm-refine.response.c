char *__cdecl get_begin(char *str, int *out_sign)
{
  int sign = 1;
  int i = 0;

  // Skip all leading '+' and '-' characters
  while (str[i] == '+' || str[i] == '-')
  {
    // Toggle the sign for every '-' encountered
    if (str[i] == '-')
    {
      sign = -sign;
    }
    i++;
  }

  *out_sign = sign;
  return &str[i];
}