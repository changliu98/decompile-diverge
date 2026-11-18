size_t __cdecl base_len(const char *name)
{
  size_t len = strlen(name);

  // Strip trailing '/' characters, stopping if only 1 character remains
  while (len > 1 && name[len - 1] == '/')
  {
    --len;
  }

  return len;
}