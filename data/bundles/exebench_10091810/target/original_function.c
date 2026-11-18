void BGBBTJ_BC7_EncodeBlock_VecSwapRGB(int *clra, int *clrb)
{
 int t;
 t=clra[0]; clra[0]=clrb[0]; clrb[0]=t;
 t=clra[1]; clra[1]=clrb[1]; clrb[1]=t;
 t=clra[2]; clra[2]=clrb[2]; clrb[2]=t;
}