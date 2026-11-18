char *__cdecl replace_char(char *str, char find, char replace)
{
  char *pos;

  // Iterate through the string, finding each occurrence of 'find'
  for (pos = strchr(str, find); pos != NULL; pos = strchr(pos + 1, find))
  {
    // Replace the found character with the new one
    *pos = replace;
  }

  return str;
}