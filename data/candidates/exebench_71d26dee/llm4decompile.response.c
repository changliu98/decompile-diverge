int obdRevConvert_2C(float val, int *A, int *B, int *C, int *D)
{
 *A = (int)(val * 1000 / 3.6);
 return 1;
}