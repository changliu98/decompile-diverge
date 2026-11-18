void swapf(float *a,float *b)

{
  float fVar1;
  float t;
  float *b_local;
  float *a_local;
  
  fVar1 = *a;
  *a = *b;
  *b = fVar1;
  return;
}