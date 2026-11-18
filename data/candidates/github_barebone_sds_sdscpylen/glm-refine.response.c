sds __cdecl sdscpylen(sds s, const char *t, size_t len)
{
  if (sdsalloc(s) < len)
  {
    s = sdsMakeRoomFor(s, len - sdslen(s));
    if (!s)
      return NULL;
  }
  
  memcpy(s, t, len);
  s[len] = '\0';
  sdssetlen(s, len);
  
  return s;
}