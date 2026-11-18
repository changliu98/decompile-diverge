void remove_all_chars(char *str,char c)

{
  char *pw;
  char *pr;
  char c_local;
  char *str_local;
  
  pw = str;
  pr = str;
  while (*pr != '\0') {
    *pw = *pr;
    pw = pw + (int)(uint)(*pw != c);
    pr = pr + 1;
  }
  *pw = '\0';
  return;
}