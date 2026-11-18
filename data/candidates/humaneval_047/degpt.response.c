float func0(float *l,int size)

{
  float fVar1;
  float temp;
  int j;
  int i;
  int size_local;
  float *l_local;
  float local_c;
  
  for (i = 0; j = i, i < size; i = i + 1) {
    while (j = j + 1, j < size) {
      if (l[j] <= l[i] && l[i] != l[j]) {
        fVar1 = l[i];
        l[i] = l[j];
        l[j] = fVar1;
      }
    }
  }
  if (size % 2 == 1) {
    local_c = l[size / 2];
  }
  else {
    local_c = (float)(DAT_00102008 * (double)(l[size / 2] + l[size / 2 + -1]));
  }
  return local_c;
}