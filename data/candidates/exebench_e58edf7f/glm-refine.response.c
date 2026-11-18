void __cdecl toUpperCase(char *str)
{
  for (int index = 0; str[index]; ++index)
  {
    if (str[index] >= 'a' && str[index] <= 'z')
      str[index] -= 32;
  }
}