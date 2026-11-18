void merge(int *A, int *B, int *C)
{
 int i,j,k;
 i=0;
 j=0;
 k=0;
 while(i<6 && j<6)
 {
  if(A[i]<B[j])
  {
   C[k]=A[i];
   i++;
  }
  else
  {
   C[k]=B[j];
   j++;
  }
  k++;
 }
 while(i<6)
 {
  C[k]=A[i];
  k++;
  i++;
 }
 while(j<6)
 {
  C[k]=B[j];
  k++;
  j++;
 }
}