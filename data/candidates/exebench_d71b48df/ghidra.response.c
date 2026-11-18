void trocar(int *p,int *q)

{
  int iVar1;
  int temp;
  int *q_local;
  int *p_local;
  
  iVar1 = *p;
  *p = *q;
  *q = iVar1;
  return;
}