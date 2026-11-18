/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void func0(float *numbers,int size,float *out)

{
  float fVar1;
  float temp;
  float diff;
  int j;
  int i;
  float min_diff;
  float *out_local;
  int size_local;
  float *numbers_local;
  
  min_diff = DAT_00102004;
  *out = *numbers;
  out[1] = numbers[1];
  for (i = 0; j = i, i < size; i = i + 1) {
    while (j = j + 1, j < size) {
      fVar1 = (float)(double)((ulong)(double)(numbers[i] - numbers[j]) & _DAT_00102010);
      if (fVar1 < min_diff) {
        *out = numbers[i];
        out[1] = numbers[j];
        min_diff = fVar1;
      }
    }
  }
  if (out[1] <= *out && *out != out[1]) {
    fVar1 = *out;
    *out = out[1];
    out[1] = fVar1;
  }
  return;
}