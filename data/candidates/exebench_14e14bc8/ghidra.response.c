void c_sysconf_(int *name,int *val,int *err)

{
  long lVar1;
  int *piVar2;
  int *err_local;
  int *val_local;
  int *name_local;
  
  lVar1 = sysconf(*name);
  *val = (int)lVar1;
  piVar2 = __errno_location();
  *err = *piVar2;
  return;
}