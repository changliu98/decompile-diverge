int obdRevConvert_42(float value, int *A, int *B, int *C, int *D)
{
 int temp;

 temp = (int)(value * 100);
 *A = temp / 256;
 *B = temp % 256;

 return 2;
}