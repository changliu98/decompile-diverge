ptrdiff_t
argmatch (const char *arg, const char *const *arglist,
          const void *vallist, size_t valsize)
{
  size_t arglen = strlen (arg); /* Length of ARG.  */

  ptrdiff_t matchind = -1;      /* Index of first nonexact match.  */
  bool ambiguous = false;       /* If true, multiple nonexact match(es).  */

  /* Test all elements for either exact match or abbreviated matches.  */
  for (size_t i = 0; arglist[i]; i++)
    {
      if (!strncmp (arglist[i], arg, arglen))
        {
          if (strlen (arglist[i]) == arglen)
            /* Exact match found.  */
            return i;
          else if (matchind == -1)
            /* First nonexact match found.  */
            matchind = i;
          else
            {
              /* Second nonexact match found.  */
              if (vallist == NULL
                  || !memeq ((char const *) vallist + valsize * matchind,
                             (char const *) vallist + valsize * i, valsize))
                {
                  /* There is a real ambiguity, or we could not
                     disambiguate. */
                  ambiguous = true;
                }
            }
        }
    }
  if (ambiguous)
    return -2;
  else
    return matchind;
}