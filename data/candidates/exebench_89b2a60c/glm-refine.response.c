char *__cdecl char_replace(char *str, char old_char, char new_char)
{
  char *found;

  // Check for null pointer or empty string
  if ( !str || !*str )
    return str;

  // Iterate through the string finding each occurrence of old_char
  for (found = strchr(str, old_char); found; found = strchr(found + 1, old_char))
  {
    *found = new_char;
  }

  return str;
}