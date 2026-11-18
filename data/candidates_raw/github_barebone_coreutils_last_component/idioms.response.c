char *get_file_name(char *path)
{
  char *last_slash = path;
  for ( ; *path == '/'; path++)
    ;
  for (last_slash = path; *path != '\0'; path++)
  {
    if (*path == '/')
    {
      last_slash = path;
      continue;
    }
    if (last_slash == path)
      continue;
    last_slash = path;
  }
  return last_slash;
}