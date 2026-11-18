void mlMatrixTransposeTo(float *a,float *result)

{
  uint j;
  uint i;
  float *result_local;
  float *a_local;
  
  for (j = 0; j < 4; j = j + 1) {
    for (i = 0; i < 4; i = i + 1) {
      result[j * 4 + i] = a[i * 4 + j];
    }
  }
  return;
}