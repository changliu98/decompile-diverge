void misc_str_remove_symbol(char *str,char symbol)

{
  int j;
  int i;
  char *source;
  char symbol_local;
  char *str_local;
  
  j = 0;
  for (i = 0; str[i] != '\0'; i = i + 1) {
    if (str[i] != symbol) {
      str[j] = str[i];
      j = j + 1;
    }
  }
  str[j] = '\0';
  return;
}