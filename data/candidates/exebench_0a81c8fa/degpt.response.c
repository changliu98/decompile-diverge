void SWAP_short(short *a,short *b)

{
  short sVar1;
  short temp;
  short *b_local;
  short *a_local;
  
  sVar1 = *a;
  *a = *b;
  *b = sVar1;
  return;
}