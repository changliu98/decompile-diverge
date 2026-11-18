int is_palindrome(char *str)
{
  int len = strlen(str);
  int i = 0;
  for (i = 0; i < len - 2; i++)
  {
    if (str[i] != str[i + 2])
      return 0;
  }
  if (str[0] == str[1])
    return 0;
  return 1;
}