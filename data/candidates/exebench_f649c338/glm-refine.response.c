char *__cdecl ft_strrev(char *str)
{
  char c;
  int len = 0;
  int left = 0;

  // Calculate the length of the string
  while (str[len])
    ++len;

  // Reverse the string in-place using a two-pointer approach
  for (int right = len - 1; right > left; --right)
  {
    c = str[right];
    str[right] = str[left];
    str[left++] = c;
  }

  return str;
}