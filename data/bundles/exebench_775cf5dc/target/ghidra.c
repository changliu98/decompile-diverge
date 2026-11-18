void AddArray2(float *a,float *b,int len)

{
  int i;
  int len_local;
  float *b_local;
  float *a_local;
  
  for (i = 0; i < len; i = i + 2) {
    b[i] = b[i] + a[i];
    b[i + 1] = b[i + 1] + a[i + 1];
  }
  return;
}