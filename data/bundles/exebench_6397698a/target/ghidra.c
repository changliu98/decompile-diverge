char * truncate_string_at_char(char *str,char chr)

{
  char *ptr;
  char chr_local;
  char *str_local;
  
  for (ptr = str; *ptr != '\0'; ptr = ptr + 1) {
    if (*ptr == chr) {
      *ptr = '\0';
    }
  }
  return str;
}