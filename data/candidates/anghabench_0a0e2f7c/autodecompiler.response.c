static size_t sdsull2str(char *dest,unsigned long i) {
  register char* s=dest;
  register unsigned long len,tmp;
  do *s++='0'+(i%10),i/=10; while(i); len=s-dest; *s=0;
  --s;
  for (; dest<s; ++dest,--s) { tmp=*dest; *dest=*s; *s=tmp; }
  return len;
}