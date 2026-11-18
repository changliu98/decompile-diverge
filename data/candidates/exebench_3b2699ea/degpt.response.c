void reverse(char *str)

{
  char cVar1;
  char c;
  int len;
  int i;
  char *str_local;
  
  for (len = 0; str[len] != '\0'; len = len + 1) {
  }
  for (i = 0; i < len / 2; i = i + 1) {
    cVar1 = str[i];
    str[i] = str[(len - i) + -1];
    str[(len - i) + -1] = cVar1;
  }
  return;
}