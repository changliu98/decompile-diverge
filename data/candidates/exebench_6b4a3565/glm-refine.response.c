char *__cdecl my_strupcase(char *str)
{
  for (size_t i = 0; str[i] != '\0'; ++i)
  {
    if (str[i] >= 'a' && str[i] <= 'z')
    {
      str[i] -= 32; // 32 is the ASCII offset between lowercase and uppercase
    }
  }
  return str;
}