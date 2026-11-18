size_t modp_rtrim(char *str,size_t len)

{
  char cVar1;
  char c;
  size_t len_local;
  char *str_local;
  
  for (len_local = len;
      (len_local != 0 &&
      ((((cVar1 = str[len_local - 1], cVar1 == ' ' || (cVar1 == '\n')) || (cVar1 == '\t')) ||
       (cVar1 == '\r')))); len_local = len_local - 1) {
    str[len_local - 1] = '\0';
  }
  return len_local;
}