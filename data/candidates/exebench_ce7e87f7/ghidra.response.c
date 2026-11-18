void BGBBTJ_BC7_EncodeBlock_VecSwapRGBA(int *clra,int *clrb)

{
  int iVar1;
  int t;
  int *clrb_local;
  int *clra_local;
  
  iVar1 = *clra;
  *clra = *clrb;
  *clrb = iVar1;
  iVar1 = clra[1];
  clra[1] = clrb[1];
  clrb[1] = iVar1;
  iVar1 = clra[2];
  clra[2] = clrb[2];
  clrb[2] = iVar1;
  iVar1 = clra[3];
  clra[3] = clrb[3];
  clrb[3] = iVar1;
  return;
}