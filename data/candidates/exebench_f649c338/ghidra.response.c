char * ft_strrev(char *str)

{
  char cVar1;
  char c;
  int j;
  int i;
  char *str_local;
  
  j = 0;
  for (i = 0; str[i] != '\0'; i = i + 1) {
  }
  for (; i = i + -1, j < i; j = j + 1) {
    cVar1 = str[i];
    str[i] = str[j];
    str[j] = cVar1;
  }
  return str;
}