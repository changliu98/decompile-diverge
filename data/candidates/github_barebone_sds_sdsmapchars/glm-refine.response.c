sds __cdecl sdsmapchars(sds s, const char *from, const char *to, size_t setlen)
{
  size_t len = sdslen(s);
  
  for (size_t j = 0; j < len; j++)
  {
    for (size_t i = 0; i < setlen; i++)
    {
      if (s[j] == from[i])
      {
        s[j] = to[i];
        break;
      }
    }
  }
  
  return s;
}