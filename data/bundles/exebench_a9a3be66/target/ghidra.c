void byte2bits(char c,char *s)

{
  int i;
  char *s_local;
  char c_local;
  
  i = 7;
  s_local = s;
  while (-1 < i) {
    *s_local = ((byte)((int)c >> ((byte)i & 0x1f)) & 1) + 0x30;
    i = i + -1;
    s_local = s_local + 1;
  }
  *s_local = '\0';
  return;
}