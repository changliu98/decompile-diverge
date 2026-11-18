sds __cdecl sdscpylen(sds s, const char *t, size_t len)
{
  size_t v3; // rax
  sds sa; // [rsp+20h] [rbp-10h]

  sa = s;
  if ( sdsalloc(s) < len )
  {
    v3 = sdslen(s);
    sa = sdsMakeRoomFor(s, len - v3);
    if ( !sa )
      return 0LL;
  }
  memcpy(sa, t, len);
  sa[len] = 0;
  sdssetlen(sa, len);
  return sa;
}