char * my_strupcase(char *str)

{
  int lp;
  char *str_local;
  char *local_10;
  
  if (str == (char *)0x0) {
    local_10 = (char *)0x0;
  }
  else {
    for (lp = 0; local_10 = str, str[lp] != '\0'; lp = lp + 1) {
      if (('`' < str[lp]) && (str[lp] < '{')) {
        str[lp] = str[lp] + -0x20;
      }
    }
  }
  return local_10;
}