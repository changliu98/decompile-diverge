int get_priority(long pid,int *priority)

{
  int iVar1;
  int *piVar2;
  int *priority_local;
  long pid_local;
  
  iVar1 = getpriority(PRIO_PROCESS,(id_t)pid);
  *priority = iVar1;
  piVar2 = __errno_location();
  return *piVar2;
}