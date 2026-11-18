ptrdiff_t
argmatch_exact (const char *arg, const char *const *arglist)
{
  /* Test elements for exact match.  */
  for (size_t i = 0; arglist[i]; i++)
    {
      if (streq (arglist[i], arg))
        return i;
    }

  return -1;
}