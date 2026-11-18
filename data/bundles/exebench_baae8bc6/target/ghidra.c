void reverse(char *str)

{
  char *pcVar1;
  char *q;
  char *str_local;
  
  pcVar1 = str;
  do {
    q = pcVar1;
    pcVar1 = q + 1;
    str_local = str;
  } while (*q != '\0');
  for (; q = q + -1, str_local < q; str_local = str_local + 1) {
    *str_local = *str_local - *q;
    *q = *q + *str_local;
    *str_local = *q - *str_local;
  }
  return;
}