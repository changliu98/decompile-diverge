void __cdecl outfname(char *s)
{
  size_t len = strlen(s);
  if (len > 0)
  {
    // 115 is the ASCII value for 's'
    s[len - 1] = 's';
  }
}