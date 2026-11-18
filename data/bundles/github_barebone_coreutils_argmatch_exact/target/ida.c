ptrdiff_t __cdecl argmatch_exact(const char *arg, const char *const *arglist)
{
  ptrdiff_t i; // [rsp+0h] [rbp-20h]

  for ( i = 0LL; arglist[i]; ++i )
  {
    if ( !strcmp(arglist[i], arg) )
      return i;
  }
  return -1LL;
}