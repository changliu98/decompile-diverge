bool __cdecl strip_trailing_slashes(char *file)
{
  char *base = last_component(file);
  
  // If the last component is empty (e.g., path ends with a slash like "foo/"), 
  // fall back to the beginning of the string.
  if (*base == '\0')
    base = file;

  // Find the end of the base component
  char *base_lim = base + base_len(base);

  // Check if there is a trailing slash and truncate the string there
  bool had_slash = (*base_lim != '\0');
  *base_lim = '\0';

  return had_slash;
}