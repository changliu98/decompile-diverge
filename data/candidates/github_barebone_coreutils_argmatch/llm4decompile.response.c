ptrdiff_t argmatch(const char *arg, const char *const *optlist,
                   const void *vallist, size_t valsize)
{
  size_t arglen = strlen(arg);
  ptrdiff_t matchind = -1;
  unsigned char ambiguous = 0;
  ptrdiff_t i;

  for (i = 0; optlist[i]; i++)
    {
      if (!strncmp(optlist[i], arg, arglen))
        {
          if (strlen(optlist[i]) == arglen)

            return i;
          else if (matchind == -1)

            matchind = i;
          else if (vallist &&
                   !memcmp((const void *) ((const char *) vallist + i * valsize),
                           (const void *) ((const char *) vallist + matchind * valsize),
                           valsize))

            ;
          else

            ambiguous = 1;
        }
    }
  if (ambiguous)
    return -2;
  else
    return matchind;
}