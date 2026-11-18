void reverse(char *str)

{
  char cVar1;
  char tmp;
  int i;
  int length;
  char *str_local;
  
  for (length = 0; str[length] != '\0'; length = length + 1) {
  }
  for (i = 0; i < length / 2; i = i + 1) {
    cVar1 = str[i];
    str[i] = str[(length - i) + -1];
    str[(length - i) + -1] = cVar1;
  }
  return;
}