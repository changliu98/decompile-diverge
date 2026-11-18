void AddArray4(float *a,float *b,int len)

{
  int i;
  int len_local;
  float *b_local;
  float *a_local;
  
  for (i = 0; i < len; i = i + 4) {
    b[i] = b[i] + a[i];
    b[i + 1] = b[i + 1] + a[i + 1];
    b[i + 2] = b[i + 2] + a[i + 2];
    b[i + 3] = b[i + 3] + a[i + 3];
  }
  return;
}