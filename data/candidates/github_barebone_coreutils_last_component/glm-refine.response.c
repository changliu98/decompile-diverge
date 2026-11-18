char *__cdecl last_component(const char *name)
{
  const char *p;
  bool last_was_slash = false;

  // Skip any leading slashes
  while (*name == '/')
    ++name;

  // Traverse the string to find the last component
  for (p = name; *p; ++p)
  {
    if (*p == '/')
    {
      last_was_slash = true;
    }
    else if (last_was_slash)
    {
      // If we encounter a non-slash character after a slash, 
      // we've entered a new path component.
      name = p;
      last_was_slash = false;
    }
  }

  return (char *)name;
}