double mat3_det(float *A)
{
 double det = 0;
 int i, j;
 double B[9];

 memset(B, 0, sizeof(B));

 for (i = 0; i < 3; i++)
  for (j = 0; j < 3; j++)
   B[i * 3 + j] = A[i * 4 + j];

 det += B[0] * ((B[4] * B[8]) - fabs(B[5] * B[7]));
 det += fabs(B[1] * (B[5] * B[6] - fabs(B[7] * B[2])));
 det += B[2] * (B[3] * B[7] - fabs(B[4] * B[6]));

 return det;
}