void __cdecl strcpymax(char *dest, const char *src, int n)
{
  int i;

  if (n)
  {
    for (i = 0; i < n - 1 && *src; ++i)
    {
      *dest++ = *src++;
    }
  }
  *dest = 0;
}