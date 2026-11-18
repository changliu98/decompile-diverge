void __cdecl InvMat22(float *invA, float *A)
{
  // A represents a 2x2 matrix:
  // [ A[0]  A[1] ]
  // [ A[2]  A[3] ]

  // Calculate the determinant: detA = A[0]*A[3] - A[1]*A[2]
  float detA = (A[0] * A[3]) - (A[1] * A[2]);

  // Calculate the inverse: (1 / detA) * [ A[3]  -A[1] ]
  //                                   [ -A[2]  A[0] ]
  float inv_detA = 1.0f / detA;

  invA[0] =  inv_detA * A[3];
  invA[1] = -inv_detA * A[1];
  invA[2] = -inv_detA * A[2];
  invA[3] =  inv_detA * A[0];
}