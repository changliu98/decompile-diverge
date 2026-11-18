char * convert_set_sign(char *s,int *sign)

{
  int *sign_local;
  char *s_local;
  
  *sign = 1;
  s_local = s;
  if (s != (char *)0x0) {
    if (*s == '+') {
      *sign = 1;
      s_local = s + 1;
    }
    else if (*s == '-') {
      *sign = -1;
      s_local = s + 1;
    }
  }
  return s_local;
}