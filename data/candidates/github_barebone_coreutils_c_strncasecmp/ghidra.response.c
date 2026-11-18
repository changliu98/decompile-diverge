int c_strncasecmp(char *s1,char *s2,size_t n)

{
  uint uVar1;
  uint uVar2;
  uchar c2;
  uchar c1;
  uchar *p2;
  uchar *p1;
  size_t n_local;
  char *s2_local;
  char *s1_local;
  int local_c;
  
  if ((s1 == s2) || (p2 = (uchar *)s2, p1 = (uchar *)s1, n_local = n, n == 0)) {
    local_c = 0;
  }
  else {
    while( true ) {
      uVar1 = c_tolower((uint)*p1);
      uVar2 = c_tolower((uint)*p2);
      n_local = n_local - 1;
      if (((n_local == 0) || ((char)uVar1 == '\0')) || ((uVar1 & 0xff) != (uVar2 & 0xff))) break;
      p1 = p1 + 1;
      p2 = p2 + 1;
    }
    local_c = (uVar1 & 0xff) - (uVar2 & 0xff);
  }
  return local_c;
}