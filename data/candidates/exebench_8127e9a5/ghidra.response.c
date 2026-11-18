void reverse(char *str)

{
  char cVar1;
  char tmp;
  size_t j;
  size_t i;
  size_t str_len;
  char *str_local;
  
  for (str_len = 0; str[str_len] != '\0'; str_len = str_len + 1) {
  }
  if (str_len != 0) {
    for (i = 0; j = str_len - 1, i < j; i = i + 1) {
      cVar1 = str[i];
      str[i] = str[j];
      str[j] = cVar1;
      str_len = j;
    }
  }
  return;
}