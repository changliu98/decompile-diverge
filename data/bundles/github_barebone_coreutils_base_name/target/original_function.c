char *
base_name (char const *name)
{
  char const *base = last_component (name);
  idx_t length;
  int dotslash_len;
  if (*base)
    {
      length = base_len (base);

      /* Collapse a sequence of trailing slashes into one.  */
      length += ISSLASH (base[length]);

      /* On systems with drive letters, "a/b:c" must return "./b:c" rather
         than "b:c" to avoid confusion with a drive letter.  On systems
         with pure POSIX semantics, this is not an issue.  */
      dotslash_len = FILE_SYSTEM_PREFIX_LEN (base) != 0 ? 2 : 0;
    }
  else
    {
      /* There is no last component, so NAME is a file system root or
         the empty string.  */
      base = name;
      length = base_len (base);
      dotslash_len = 0;
    }

  char *p = ximalloc (dotslash_len + length + 1);
  if (dotslash_len)
    {
      p[0] = '.';
      p[1] = '/';
    }

  /* Finally, copy the basename.  */
  memcpy (p + dotslash_len, base, length);
  p[dotslash_len + length] = '\0';
  return p;
}