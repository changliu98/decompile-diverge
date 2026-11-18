void InvMat22(float *invA,float *A)

{
  float fVar1;
  float detA;
  float *A_local;
  float *invA_local;
  
  fVar1 = *A * A[3] + -(A[1] * A[2]);
  *invA = (DAT_00102004 / fVar1) * A[3];
  invA[1] = (DAT_00102008 / fVar1) * A[1];
  invA[2] = (DAT_00102008 / fVar1) * A[2];
  invA[3] = (DAT_00102004 / fVar1) * *A;
  return;
}