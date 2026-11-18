void interchange(int *u,int *v)

{
  int iVar1;
  int temp;
  int *v_local;
  int *u_local;
  
  iVar1 = *u;
  *u = *v;
  *v = iVar1;
  return;
}