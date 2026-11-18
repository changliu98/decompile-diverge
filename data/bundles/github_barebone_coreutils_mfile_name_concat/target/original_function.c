char *
mfile_name_concat (char const *dir, char const *base, char **base_in_result)
{
  char const *dirbase = last_component (dir);
  size_t dirbaselen = base_len (dirbase);
  size_t dirlen = dirbase - dir + dirbaselen;
  size_t baselen = strlen (base);
  char sep = '\0';
  if (dirbaselen)
    {
      /* DIR is not a file system root, so separate with / if needed.  */
      if (! ISSLASH (dir[dirlen - 1]) && ! ISSLASH (*base))
        sep = '/';
    }
  else if (ISSLASH (*base))
    {
      /* DIR is a file system root and BASE begins with a slash, so
         separate with ".".  For example, if DIR is "/" and BASE is
         "/foo" then return "/./foo", as "//foo" would be wrong on
         some POSIX systems.  A fancier algorithm could omit "." in
         some cases but is not worth the trouble.  */
      sep = '.';
    }

  char *p_concat = malloc (dirlen + (sep != '\0')  + baselen + 1);
  if (p_concat == NULL)
    return NULL;

  {
    char *p;

    p = mempcpy (p_concat, dir, dirlen);
    *p = sep;
    p += sep != '\0';

    if (base_in_result)
      *base_in_result = p;

    p = mempcpy (p, base, baselen);
    *p = '\0';
  }

  return p_concat;
}