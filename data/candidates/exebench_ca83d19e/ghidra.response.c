char * ft_strupcase(char *str)

{
  int i;
  char *str_local;
  
  for (i = 0; str[i] != '\0'; i = i + 1) {
    if (('`' < str[i]) && (str[i] < '{')) {
      str[i] = str[i] + -0x20;
    }
  }
  return str;
}