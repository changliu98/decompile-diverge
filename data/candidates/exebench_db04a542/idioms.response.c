char *checkpath(char *path, char *srcpath)
{
  char *p = path;
  if (path && srcpath)
  {
    while (*srcpath)
    {
      if (*srcpath == '\\')
      {
        *p++ = '/';
        srcpath++;
      }
      else
      {
        *p++ = *srcpath++;
      }
    }
    *p = *srcpath;
  }
  return path;
}