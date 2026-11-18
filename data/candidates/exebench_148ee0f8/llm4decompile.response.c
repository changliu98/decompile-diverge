void InvMat22(float *invA, float *A)
{
  float detA = A[0]*A[3] - A[1]*A[2];
  invA[0] = 1.0f/detA * A[3];
  invA[1] = -1.0f/detA * A[1];
  invA[2] = -1.0f/detA * A[2];
  invA[3] = 1.0f/detA * A[0];
}