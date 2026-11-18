char * mdir_name(char *file)

{
  char *dir;
  _Bool append_dot;
  size_t length;
  char *file_local;
  char *local_10;
  
  length = dir_len(file);
  local_10 = malloc(length + (length == 0) + 1);
  if (local_10 == (char *)0x0) {
    local_10 = (char *)0x0;
  }
  else {
    memcpy(local_10,file,length);
    if (length == 0) {
      length = 1;
      *local_10 = '.';
    }
    local_10[length] = '\0';
  }
  return local_10;
}