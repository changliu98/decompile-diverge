void sdsrange(sds s,ssize_t start,ssize_t end)

{
  size_t sVar1;
  size_t local_38;
  size_t len;
  size_t newlen;
  ssize_t end_local;
  ssize_t start_local;
  sds s_local;
  
  sVar1 = sdslen(s);
  if (sVar1 != 0) {
    start_local = start;
    if ((start < 0) && (start_local = sVar1 + start, start_local < 0)) {
      start_local = 0;
    }
    end_local = end;
    if ((end < 0) && (end_local = sVar1 + end, end_local < 0)) {
      end_local = 0;
    }
    if (end_local < start_local) {
      local_38 = 0;
    }
    else {
      local_38 = (end_local - start_local) + 1;
    }
    newlen = local_38;
    if (local_38 != 0) {
      if (start_local < (long)sVar1) {
        if ((long)sVar1 <= end_local) {
          newlen = sVar1 - start_local;
        }
      }
      else {
        newlen = 0;
      }
    }
    if ((start_local != 0) && (newlen != 0)) {
      memmove(s,s + start_local,newlen);
    }
    s[newlen] = '\0';
    sdssetlen(s,newlen);
  }
  return;
}