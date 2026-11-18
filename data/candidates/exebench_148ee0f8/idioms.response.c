void InvMat22(float *invA, float *A)
{
  float detA = A[0]*A[3] - A[1]*A[2];
  invA[0] = A[3]/detA;
  invA[1] = -A[1]/detA;
  invA[2] = -A[2]/detA;
  invA[3] = A[0]/detA;
}