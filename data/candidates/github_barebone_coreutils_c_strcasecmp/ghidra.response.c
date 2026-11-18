int c_strcasecmp(char *s1,char *s2)

{
  uint uVar1;
  uint uVar2;
  uchar c2;
  uchar c1;
  uchar *p2;
  uchar *p1;
  char *s2_local;
  char *s1_local;
  int local_c;
  
  p2 = (uchar *)s2;
  p1 = (uchar *)s1;
  if (s1 == s2) {
    local_c = 0;
  }
  else {
    while( true ) {
      uVar1 = c_tolower((uint)*p1);
      uVar2 = c_tolower((uint)*p2);
      if (((char)uVar1 == '\0') || ((uVar1 & 0xff) != (uVar2 & 0xff))) break;
      p1 = p1 + 1;
      p2 = p2 + 1;
    }
    local_c = (uVar1 & 0xff) - (uVar2 & 0xff);
  }
  return local_c;
}