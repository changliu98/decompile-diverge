void QuaternionMult(float *pfQOut,float *pfQIn1,float *pfQIn2)

{
  float *pfQIn2_local;
  float *pfQIn1_local;
  float *pfQOut_local;
  
  *pfQOut = -pfQIn2[3] * pfQIn1[3] +
            -pfQIn2[2] * pfQIn1[2] + *pfQIn2 * *pfQIn1 + -(pfQIn2[1] * pfQIn1[1]);
  pfQOut[1] = pfQIn2[3] * pfQIn1[2] +
              -pfQIn2[2] * pfQIn1[3] + pfQIn2[1] * *pfQIn1 + *pfQIn2 * pfQIn1[1];
  pfQOut[2] = -pfQIn2[3] * pfQIn1[1] +
              -pfQIn2[2] * *pfQIn1 + *pfQIn2 * pfQIn1[2] + pfQIn2[1] * pfQIn1[3];
  pfQOut[3] = pfQIn2[3] * *pfQIn1 +
              -pfQIn2[2] * pfQIn1[1] + *pfQIn2 * pfQIn1[3] + -(pfQIn2[1] * pfQIn1[2]);
  return;
}