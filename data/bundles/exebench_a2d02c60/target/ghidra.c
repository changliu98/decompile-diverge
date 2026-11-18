int ft_pn(char *str,int *p_n,int i)

{
  bool bVar1;
  int i_local;
  int *p_n_local;
  char *str_local;
  
  i_local = i;
  while( true ) {
    bVar1 = true;
    if ((str[i_local] != ' ') && (bVar1 = false, '\b' < str[i_local])) {
      bVar1 = str[i_local] < '\x0e';
    }
    if (!bVar1) break;
    i_local = i_local + 1;
  }
  if (str[i_local] == '\0') {
    *p_n = -3;
  }
  if (str[i_local] == '-') {
    *p_n = -2;
  }
  return i_local;
}