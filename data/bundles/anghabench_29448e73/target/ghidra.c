int hex_to_int(char *s,int *x)

{
  int i;
  int *x_local;
  char *s_local;
  
  *x = 0;
  i = 0;
  do {
    if (7 < i) {
      return 1;
    }
    if ((s[i] < '0') || ('9' < s[i])) {
      if ((s[i] < 'a') || ('f' < s[i])) {
        return 0;
      }
      *x = *x * 0x10 + (int)s[i] + -0x57;
    }
    else {
      *x = *x * 0x10 + (int)s[i] + -0x30;
    }
    i = i + 1;
  } while( true );
}