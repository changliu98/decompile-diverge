int __cdecl func0(const char *str)
{
  int str_len; // [rsp+4h] [rbp-Ch]

  str_len = strlen(str);
  return (str_len + 1) * str_len / 2;
}