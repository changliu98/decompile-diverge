void __cdecl strupper(char *str)
{
  for (int i = 0; str[i]; ++i)
  {
    if (str[i] >= 'a' && str[i] <= 'z')
      str[i] -= 'a' - 'A'; // 32
  }
}