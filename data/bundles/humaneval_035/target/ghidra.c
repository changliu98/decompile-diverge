float func0(float *l,int size)

{
  int i;
  float max;
  int size_local;
  float *l_local;
  
  max = DAT_00102004;
  for (i = 0; i < size; i = i + 1) {
    if (max < l[i]) {
      max = l[i];
    }
  }
  return max;
}