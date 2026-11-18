void swap(float *min,float *max)

{
  float fVar1;
  float temp;
  float *max_local;
  float *min_local;
  
  if (*max <= *min && *min != *max) {
    fVar1 = *max;
    *max = *min;
    *min = fVar1;
  }
  return;
}