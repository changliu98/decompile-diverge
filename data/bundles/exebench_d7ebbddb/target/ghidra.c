void raw_relu_bulk_apply_function(int n,float *ptr)

{
  float fVar1;
  int i;
  float *ptr_local;
  int n_local;
  
  for (i = 0; i < n; i = i + 1) {
    if (ptr[i] <= 0.0) {
      fVar1 = 0.0;
    }
    else {
      fVar1 = ptr[i];
    }
    ptr[i] = fVar1;
  }
  return;
}