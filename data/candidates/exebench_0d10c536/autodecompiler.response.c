void bitrv216(double *A)
{
 double temp;

 temp = A[2];
 A[2] = A[8];
 A[8] = A[4];
 A[4] = A[10];
 A[10] = A[12];
 A[12] = A[6];
 A[6] = A[14];
 A[14] = temp;

 temp = A[16];
 A[16] = A[18];
 A[18] = A[20];
 A[20] = A[22];
 A[22] = A[24];
 A[24] = A[26];
 A[26] = A[28];
 A[28] = A[30];
}