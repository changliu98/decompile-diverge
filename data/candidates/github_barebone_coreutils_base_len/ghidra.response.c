size_t base_len(char *name)

{
  bool bVar1;
  size_t prefix_len;
  size_t len;
  char *name_local;
  
  len = strlen(name);
  while( true ) {
    bVar1 = false;
    if (1 < len) {
      bVar1 = name[len - 1] == '/';
    }
    if (!bVar1) break;
    len = len - 1;
  }
  return len;
}