void BGBBTJ_BC7_EncodeBlock_VecSwapA(int *clra,int *clrb)

{
  int iVar1;
  int t;
  int *clrb_local;
  int *clra_local;
  
  iVar1 = clra[3];
  clra[3] = clrb[3];
  clrb[3] = iVar1;
  return;
}