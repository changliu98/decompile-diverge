char *__cdecl func0(const char *str, char ch_0)
{
  int len = strlen(str);
  int first = -1;
  int last = -1;

  // Locate the first and last index where str[i] == ch_0
  for (int i = 0; i < len; ++i)
  {
    if (str[i] == ch_0)
    {
      if (first == -1)
        first = i;
      last = i;
    }
  }

  // Not found, or only a single occurrence: return a verbatim copy.
  if (first == -1 || last == -1 || first == last)
  {
    char *copy = (char *)malloc(len + 1);
    strcpy(copy, str);
    return copy;
  }

  // Allocate buffer for str minus the two removed characters plus NUL.
  char *new_str = (char *)malloc(len - 2 + 1);
  int new_index = 0;

  // Copy segment before the first occurrence:  str[0 .. first-1]
  for (int i = 0; i < first; ++i)
    new_str[new_index++] = str[i];

  // Copy segment between the two occurrences: str[first+1 .. last-1]
  for (int i = first + 1; i < last; ++i)
    new_str[new_index++] = str[i];

  // Copy segment after the last occurrence:   str[last+1 .. len-1]
  for (int i = last + 1; i < len; ++i)
    new_str[new_index++] = str[i];

  new_str[new_index] = '\0';
  return new_str;
}