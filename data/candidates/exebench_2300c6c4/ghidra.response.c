char * strtoupper(char *s)

{
  char cVar1;
  int len;
  int i;
  char *s_local;
  
  for (i = 0; i < 8; i = i + 1) {
    if ((s[i] < 'a') || ('z' < s[i])) {
      cVar1 = s[i];
    }
    else {
      cVar1 = s[i] + -0x20;
    }
    s[i] = cVar1;
  }
  return s;
}