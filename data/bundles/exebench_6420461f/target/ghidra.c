/* WARNING: Enum "__rlimit_resource": Some values do not have unique names */

void ulimit_stack(long *rlim_cur,long *rlim_max,int *ierr)

{
  int iVar1;
  rlimit rlim;
  int result;
  int *ierr_local;
  long *rlim_max_local;
  long *rlim_cur_local;
  
  rlim.rlim_cur = DAT_00102008;
  rlim.rlim_max = DAT_00102010;
  result = setrlimit(RLIMIT_STACK,(rlimit *)&rlim);
  if ((result == -1) && (iVar1 = getrlimit(RLIMIT_STACK,(rlimit *)&rlim), iVar1 == 0)) {
    rlim.rlim_cur = rlim.rlim_max;
    result = setrlimit(RLIMIT_STACK,(rlimit *)&rlim);
  }
  *ierr = result;
  *rlim_cur = -1;
  *rlim_max = -1;
  iVar1 = getrlimit(RLIMIT_STACK,(rlimit *)&rlim);
  if (iVar1 == 0) {
    *rlim_cur = rlim.rlim_cur;
    *rlim_max = rlim.rlim_max;
  }
  return;
}