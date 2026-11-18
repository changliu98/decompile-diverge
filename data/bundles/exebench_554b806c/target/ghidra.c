_Bool is_empty(float *spectrum,int N)

{
  int k;
  int N_local;
  float *spectrum_local;
  
  k = 0;
  while( true ) {
    if (N < k) {
      return true;
    }
    if (DAT_00102020 < spectrum[k]) break;
    k = k + 1;
  }
  return false;
}