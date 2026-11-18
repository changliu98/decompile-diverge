void BGBBTJ_BC7_EncodeBlock_VecSwapB(int *clra,int *clrb)

{
  int iVar1;
  int t;
  int *clrb_local;
  int *clra_local;
  
  iVar1 = clra[2];
  clra[2] = clrb[2];
  clrb[2] = iVar1;
  return;
}