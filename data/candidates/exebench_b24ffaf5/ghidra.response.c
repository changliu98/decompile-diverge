int OS_file_open(unsigned_long *p_file_handle,char *p_filename)

{
  int iVar1;
  char *p_filename_local;
  unsigned_long *p_file_handle_local;
  undefined4 local_c;
  
  iVar1 = open(p_filename,0);
  *p_file_handle = (long)iVar1;
  if (*p_file_handle == 0xffffffffffffffff) {
    local_c = 0x1004;
  }
  else {
    local_c = 0;
  }
  return local_c;
}