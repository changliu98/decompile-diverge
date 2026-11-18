void BGBBTJ_BC7_EncodeBlock_VecSwapB(int *clra, int *clrb)
{
 int t;

 t=clra[2]; clra[2]=clrb[2]; clrb[2]=t;
}