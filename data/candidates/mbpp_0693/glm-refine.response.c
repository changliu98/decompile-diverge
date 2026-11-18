char *__cdecl func0(const char *text1)
{
  size_t i;
  size_t j;
  int space_found;
  char *result;
  size_t len;

  if (!text1)
    return NULL;

  len = strlen(text1);
  result = (char *)malloc(len + 1);
  if (!result)
    return NULL;

  i = 0;
  j = 0;
  space_found = 0;

  while (text1[i])
  {
    if (text1[i] == ' ')
    {
      if (!space_found)
      {
        result[j++] = ' ';
        space_found = 1;
      }
    }
    else
    {
      result[j++] = text1[i];
      space_found = 0;
    }
    ++i;
  }

  result[j] = '\0';
  return result;
}