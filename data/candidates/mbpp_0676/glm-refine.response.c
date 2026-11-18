char *__cdecl func0(const char *text1)
{
  size_t len = strlen(text1);
  char *result = (char *)malloc(len + 1);
  
  if (!result)
    return NULL;

  size_t j = 0;
  for (size_t i = 0; i < len; ++i)
  {
    // The original expression `(*__ctype_b_loc())[(unsigned __int8)text1[i]] & 8` 
    // checks the glibc ctype bitmask. The mask `8` corresponds to `_ISprint` (printable characters).
    if (isprint((unsigned char)text1[i]))
    {
      result[j++] = text1[i];
    }
  }
  
  result[j] = '\0';
  return result;
}