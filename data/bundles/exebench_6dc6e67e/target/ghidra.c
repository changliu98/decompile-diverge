void copia(char *dest,char *source)

{
  char *source_local;
  char *dest_local;
  
  source_local = source;
  dest_local = dest;
  while (*source_local != '\0') {
    *dest_local = *source_local;
    source_local = source_local + 1;
    dest_local = dest_local + 1;
  }
  *dest_local = '\0';
  return;
}