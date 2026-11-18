sds sdsmapchars(sds s,char *from,char *to,size_t setlen)

{
  size_t sVar1;
  size_t l;
  size_t i;
  size_t j;
  size_t setlen_local;
  char *to_local;
  char *from_local;
  sds s_local;
  
  sVar1 = sdslen(s);
  j = 0;
  do {
    if (sVar1 <= j) {
      return s;
    }
    for (i = 0; i < setlen; i = i + 1) {
      if (s[j] == from[i]) {
        s[j] = to[i];
        break;
      }
    }
    j = j + 1;
  } while( true );
}