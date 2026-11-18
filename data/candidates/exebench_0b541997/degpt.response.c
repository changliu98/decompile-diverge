void lemon_strcpy(char *dest,char *src)

{
  char cVar1;
  char *src_local;
  char *dest_local;
  
  src_local = src;
  dest_local = dest;
  do {
    cVar1 = *src_local;
    *dest_local = cVar1;
    src_local = src_local + 1;
    dest_local = dest_local + 1;
  } while (cVar1 != '\0');
  return;
}