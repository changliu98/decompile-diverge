char * js_itoa(char *out,uint a)

{
  uint i;
  char *s;
  char buf [32];
  uint a_local;
  char *out_local;
  
  i = 0;
  for (a_local = a; a_local != 0; a_local = a_local / 10) {
    buf[i] = (char)((ulong)a_local % 10) + '0';
    i = i + 1;
  }
  s = out;
  if (i == 0) {
    i = 1;
    buf[0] = '0';
  }
  while (i != 0) {
    i = i - 1;
    *s = buf[i];
    s = s + 1;
  }
  *s = '\0';
  return out;
}