void swap(float *a,float *b)

{
  float fVar1;
  float temp;
  float *b_local;
  float *a_local;
  
  fVar1 = *a;
  *a = *b;
  *b = fVar1;
  return;
}