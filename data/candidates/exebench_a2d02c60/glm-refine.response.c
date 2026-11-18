int __cdecl ft_pn(const char *str, int *p_n, int i)
{
  // Skip leading whitespaces (space, \t, \n, \v, \f, \r)
  while (isspace((unsigned char)str[i]))
    ++i;

  // Check for end of string
  if (str[i] == '\0')
    *p_n = -3;
  // Check for minus sign
  else if (str[i] == '-')
    *p_n = -2;

  return i;
}