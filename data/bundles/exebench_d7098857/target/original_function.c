void misc_str_remove_symbol(char *str, char symbol)
{
 char *source = str;
 int i, j = 0;

 for (i = 0; source[i] != '\0'; i++) {
  if (source[i] != symbol) {
   str[j] = source[i];
   j++;
  }
 }
 str[j] = '\0';
}