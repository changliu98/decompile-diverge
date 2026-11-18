ptrdiff_t __cdecl argmatch_exact(const char *arg, const char *const *arglist)
{
  ptrdiff_t i;

  for (i = 0; arglist[i] != NULL; ++i)
  {
    if (strcmp(arglist[i], arg) == 0)
      return i;
  }
  
  return -1;
}