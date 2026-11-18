static size_t sdsull2str(char *dest,unsigned long i) {
  register char* s=dest;
  size_t len;
  do *s++ = '0' + (i%10); while(i/=10);
  len=s-dest; *s=0; --s;
  for (; dest<s; ++dest,--s) {
    char tmp=*dest;
    *dest=*s;
    *s=tmp;
  }
  return len;
}