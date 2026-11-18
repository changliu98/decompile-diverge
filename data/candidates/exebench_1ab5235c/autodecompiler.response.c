void BGBBTJ_BC7_EncodeBlock_VecSwapB(int *px, int *py)
{
   int temp;
   temp = *px;
   *px = *py;
   *py = temp;
}