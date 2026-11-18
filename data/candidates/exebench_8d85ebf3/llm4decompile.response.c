int obdRevConvert_04(float val, int *A, int *B, int *C, int *D)
{
 *A = (int)(val * 60 / 1000);
 return 1;
}