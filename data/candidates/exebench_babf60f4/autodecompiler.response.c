void matmult(float (*a)[5], float (*b)[5], float (*c)[5])
{
 int i, j, k;
 for (i = 0; i < 5; i++)
 {
  for (j = 0; j < 5; j++)
  {
   *(*(c + i) + j) = 0;
   for (k = 0; k < 5; k++)
   {
    *(*(c + i) + j) += *(*(a + i) + k) * *(*(b + k) + j);
   }
  }
 }
}