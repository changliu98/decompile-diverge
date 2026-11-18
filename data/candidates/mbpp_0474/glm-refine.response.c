char *func0(char *str1, char ch_0, char newch)
{
  strcpy(func0_str2, str1);
  for (size_t i = 0; func0_str2[i]; ++i)
  {
    if (func0_str2[i] == ch_0)
      func0_str2[i] = newch;
  }
  return func0_str2;
}