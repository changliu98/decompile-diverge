char *__cdecl my_strupcase(char *str)
{
  for (int i = 0; str[i]; ++i)
  {
    if (str[i] >= 'a' && str[i] <= 'z')
      str[i] -= 32; // 32 is the ASCII difference between lowercase and uppercase
  }
  return str;
}