char *__cdecl tcp_strflags(char *s, unsigned int flags)
{
  const char *tcp_flag_chars = "FSRPAUYX";
  char *p = s;
  
  for (int bit = 0; bit < 8; ++bit)
  {
    if ((flags & (1 << bit)) != 0)
    {
      *p++ = tcp_flag_chars[bit];
    }
  }
  
  *p = '\0';
  return s;
}