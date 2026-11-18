char * convert_set_base(char *s,int *base)

{
  int *base_local;
  char *s_local;
  
  *base = 10;
  s_local = s;
  if (((s != (char *)0x0) && (*s == '0')) &&
     ((s_local = s + 1, *s_local == 'x' || (*s_local == 'X')))) {
    *base = 0x10;
    s_local = s + 2;
  }
  return s_local;
}