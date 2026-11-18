char *__cdecl base_name(const char *name)
{
  char *p;
  idx_t length;
  const char *base;

  base = last_component(name);
  
  if (*base)
  {
    // Get the length of the base component.
    // If the component ends with a trailing slash ('/' == 47), include it in the length.
    length = base_len(base) + (base[base_len(base)] == '/');
  }
  else
  {
    // If last_component returned an empty string, fall back to using the original name.
    base = name;
    length = base_len(name);
  }

  // Allocate memory for the string plus the null terminator.
  p = (char *)ximalloc(length + 1);
  
  // Copy the string and null-terminate it.
  memcpy(p, base, length);
  p[length] = '\0';
  
  return p;
}