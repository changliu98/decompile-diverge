void BGBBTJ_BC7_EncodeBlock_VecSwapA(byte *clra, byte *clrb)
{
 byte *ct;
 byte t;

 ct=clra+3; t=*ct; *ct=*clrb; *clrb=t;
}