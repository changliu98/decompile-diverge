void remove_spaces(char *str, char *dest)
{
 int i = 0, j = 0;

 while (1) {
  if (str[i] == '\0') {
   dest[j] = '\0';
   return;
  }
  if (!(((*___ctype_b_loc ())[(unsigned char)(str[i])] & (int)32768) != 0)) {
   dest[j++] = str[i];
  }
  i++;
 }
}