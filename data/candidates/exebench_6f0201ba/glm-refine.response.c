void __cdecl reverse(char *str)
{
  int length = strlen(str);

  for (int i = 0; i < length / 2; ++i)
  {
    char tmp = str[i];
    str[i] = str[length - i - 1];
    str[length - i - 1] = tmp;
  }
}