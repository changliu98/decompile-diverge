char * my_strupcase(char *str)

{
  int lp;
  char *str_local;
  
  for (lp = 0; str[lp] != '\0'; lp = lp + 1) {
    if (('`' < str[lp]) && (str[lp] < '{')) {
      str[lp] = str[lp] + -0x20;
    }
  }
  return str;
}