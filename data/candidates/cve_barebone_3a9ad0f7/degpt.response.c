double ** AcquireBilateralTLS(size_t number_threads,size_t width,size_t height)

{
  double *pdVar1;
  double **ppdVar2;
  ssize_t i;
  double **weights;
  size_t height_local;
  size_t width_local;
  size_t number_threads_local;
  double **local_10;
  
  local_10 = AcquireQuantumMemory(number_threads + 1,8);
  if (local_10 == (double **)0x0) {
    local_10 = (double **)0x0;
  }
  else {
    memset(local_10,0,number_threads << 3);
    for (i = 0; i <= (long)number_threads; i = i + 1) {
      pdVar1 = AcquireQuantumMemory(width,height << 3);
      local_10[i] = pdVar1;
      if (local_10[i] == (double *)0x0) {
        ppdVar2 = DestroyBilateralTLS(number_threads,local_10);
        return ppdVar2;
      }
    }
  }
  return local_10;
}