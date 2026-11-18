long shmDetach(float *addr)

{
  int iVar1;
  float *addr_local;
  
  iVar1 = shmdt(addr);
  return (long)iVar1;
}