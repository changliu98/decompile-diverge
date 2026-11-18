void swap(uint *p,uint *q)

{
  uint uVar1;
  uint x;
  uint *q_local;
  uint *p_local;
  
  uVar1 = *p;
  *p = *q;
  *q = uVar1;
  return;
}