void ddelete_c(char *path,int *iostat)

{
  int iVar1;
  int *piVar2;
  undefined4 local_1c;
  int *iostat_local;
  char *path_local;
  
  iVar1 = unlink(path);
  if (iVar1 == 0) {
    local_1c = 0;
  }
  else {
    piVar2 = __errno_location();
    local_1c = *piVar2;
  }
  *iostat = local_1c;
  return;
}