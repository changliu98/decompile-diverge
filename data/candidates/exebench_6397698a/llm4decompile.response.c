char *truncate_string_at_char(char *str, char chr)
{
 char *ptr = str;

 while (*ptr != '\0') {
  if (*ptr == chr) {
   *ptr = '\0';
  }
  ptr++;
 }

 return str;
}