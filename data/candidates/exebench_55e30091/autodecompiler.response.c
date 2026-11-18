void BGBBTJ_BC7_EncodeBlock_VecSwapA(int *a, int *b)
{
 int temp = *(a + 3);
 *(a + 3) = *(b + 3);
 *(b + 3) = temp;
}