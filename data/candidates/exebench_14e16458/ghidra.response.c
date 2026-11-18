void int_to_str(uint n,char *str)

{
  int i;
  char *str_local;
  uint n_local;
  
  n_local = n;
  for (i = 9; -1 < i; i = i + -1) {
    str[i] = (char)(n_local % 10) + '0';
    n_local = n_local / 10;
  }
  str[10] = '\0';
  return;
}