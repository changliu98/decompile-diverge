int obdRevConvert_45(float input, int *A, int *B, int *C, int *D)
{
 *A = (int)(input * 1000 / 10);
 return 1;
}