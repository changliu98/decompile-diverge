int func0(char *str)

{
  size_t str_length;
  int unused_length;
  char *local_str;
  
  str_length = strlen(str);
  return ((int)str_length * ((int)str_length + 1)) / 2;
}