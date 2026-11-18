int __cdecl parse_width(const char *str, size_t *len_p)
{
  size_t i;
  int val = 0;

  // Iterate over the string as long as the current character is a digit ('0'-'9')
  for (i = 0; str[i] >= '0' && str[i] <= '9'; ++i)
  {
    // Shift the current value by one decimal place and add the new digit
    val = (val * 10) + (str[i] - '0');
  }

  *len_p = i;
  return val;
}