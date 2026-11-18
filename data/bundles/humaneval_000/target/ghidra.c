/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int func0(float *numbers,int size,float threshold)

{
  int j;
  int i;
  float threshold_local;
  int size_local;
  float *numbers_local;
  
  i = 0;
  do {
    j = i;
    if (size <= i) {
      return 0;
    }
    while (j = j + 1, j < size) {
      if ((double)((ulong)(double)(numbers[i] - numbers[j]) & _DAT_00102010) < (double)threshold) {
        return 1;
      }
    }
    i = i + 1;
  } while( true );
}