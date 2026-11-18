int last_slash(char *path,int *number_found,int *path_size)

{
  int lasti;
  int found;
  int i;
  int *path_size_local;
  int *number_found_local;
  char *path_local;
  
  found = 0;
  lasti = 0;
  for (i = 0; path[i] != '\0' && i < 0x100; i = i + 1) {
    if (path[i] == '/') {
      found = found + 1;
      lasti = i;
    }
  }
  *number_found = found;
  *path_size = i;
  return lasti;
}