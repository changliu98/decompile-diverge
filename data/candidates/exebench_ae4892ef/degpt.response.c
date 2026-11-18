char * my_strcpy(char *dst,char *str)

{
  char *destination;
  char *str_local;
  char *dst_local;
  
  dst_local = dst;
  for (str_local = str; *str_local != '\0'; str_local = str_local + 1) {
    *dst_local = *str_local;
    dst_local = dst_local + 1;
  }
  *dst_local = '\0';
  return dst;
}