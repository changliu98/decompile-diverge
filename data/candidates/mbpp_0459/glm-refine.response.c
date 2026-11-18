char *__cdecl func0(const char *str1)
{
  size_t len = strlen(str1);
  char *result = (char *)malloc(len + 1);
  
  if (!result)
    return NULL;

  size_t j = 0;
  for (size_t i = 0; i < len; ++i)
  {
    // The original expression checks the glibc internal ctype table for the 'space' bit.
    // This is equivalent to the standard isspace() function.
    if (!isspace((unsigned char)str1[i]))
    {
      result[j++] = str1[i];
    }
  }
  
  result[j] = '\0';
  return result;
}