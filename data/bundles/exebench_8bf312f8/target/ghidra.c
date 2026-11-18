void twoValueSwap(float *valueA,float *valueB)

{
  float fVar1;
  float temp;
  float *valueB_local;
  float *valueA_local;
  
  fVar1 = *valueA;
  *valueA = *valueB;
  *valueB = fVar1;
  return;
}