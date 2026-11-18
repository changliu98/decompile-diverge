int __cdecl func0(const char *txt)
{
  int len = strlen(txt);
  if (len == 0)
    return 0;

  unsigned char last_char = txt[len - 1];
  
  // 0x400 corresponds to the _ISspace flag in glibc's __ctype_b_loc table
  if (!isspace(last_char))
    return 0;

  if (len == 1)
    return 1;

  unsigned char second_last_char = txt[len - 2];
  return !isspace(second_last_char);
}