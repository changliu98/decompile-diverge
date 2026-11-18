int g(int *p,short *q)

{
  short sVar1;
  int x;
  short *q_local;
  int *p_local;
  
  sVar1 = *q;
  *p = 10;
  return (int)sVar1;
}