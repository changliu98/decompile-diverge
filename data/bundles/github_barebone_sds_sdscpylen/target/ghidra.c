sds sdscpylen(sds s,char *t,size_t len)

{
  size_t sVar1;
  size_t len_local;
  char *t_local;
  sds s_local;
  
  sVar1 = sdsalloc(s);
  s_local = s;
  if (sVar1 < len) {
    sVar1 = sdslen(s);
    s_local = sdsMakeRoomFor(s,len - sVar1);
    if (s_local == (sds)0x0) {
      return (sds)0x0;
    }
  }
  memcpy(s_local,t,len);
  s_local[len] = '\0';
  sdssetlen(s_local,len);
  return s_local;
}