char *__cdecl upcase(char *str)
{
  for (size_t i = 0; str[i] != '\0'; ++i)
  {
    if (str[i] >= 'a' && str[i] <= 'z')
      str[i] = str[i] - 'a' + 'A';
  }
  return str;
}