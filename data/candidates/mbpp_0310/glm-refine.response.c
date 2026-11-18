char *__cdecl func0(const char *str, char *result)
{
  size_t j = 0;
  size_t len = strlen(str);

  for (size_t i = 0; i < len; ++i)
  {
    // 0x2000 corresponds to the _ISspace flag in the glibc ctype bitmasks
    if (!isspace((unsigned char)str[i]))
    {
      result[j++] = str[i];
    }
  }
  
  result[j] = '\0';
  return result;
}