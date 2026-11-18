char * get_next_file(FILE *VFile,char *ptr)

{
  size_t sVar1;
  char *ret;
  char *ptr_local;
  FILE *VFile_local;
  char *local_10;
  
  local_10 = fgets(ptr,0x400,(FILE *)VFile);
  if (local_10 == (char *)0x0) {
    local_10 = (char *)0x0;
  }
  else {
    sVar1 = strlen(ptr);
    if (ptr[sVar1 - 1] == '\n') {
      sVar1 = strlen(ptr);
      ptr[sVar1 - 1] = '\0';
    }
  }
  return local_10;
}