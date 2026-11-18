char * stpCpy(char *dest,char *src)

{
  char cVar1;
  char *src_local;
  char *dest_local;
  
  src_local = src;
  dest_local = dest;
  while( true ) {
    cVar1 = *src_local;
    *dest_local = cVar1;
    if (cVar1 == '\0') break;
    dest_local = dest_local + 1;
    src_local = src_local + 1;
  }
  return dest_local;
}