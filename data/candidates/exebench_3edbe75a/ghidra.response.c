int cf_pipe(int *fds)

{
  int iVar1;
  int *fds_local;
  
  iVar1 = pipe(fds);
  return iVar1;
}