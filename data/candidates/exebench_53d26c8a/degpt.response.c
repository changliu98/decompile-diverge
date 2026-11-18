void swap(int *Aj,int *Aj1)

{
  int iVar1;
  int originAj;
  int *Aj1_local;
  int *Aj_local;
  
  iVar1 = *Aj;
  *Aj = *Aj1;
  *Aj1 = iVar1;
  return;
}