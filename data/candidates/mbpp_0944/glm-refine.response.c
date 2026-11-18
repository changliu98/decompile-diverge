int __cdecl func0(const char *text)
{
  for (int i = 0; text[i] != '\0'; ++i)
  {
    // __ctype_b_loc() returns a pointer to the current thread's ctype table.
    // The bitmask 0x800 corresponds to the `_ISblank` flag in glibc's ctype.h.
    if (isblank(text[i]))
    {
      return i;
    }
  }
  return -1;
}