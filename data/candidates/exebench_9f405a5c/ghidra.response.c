void copyvector(float *a,float *b)

{
  float *b_local;
  float *a_local;
  
  *a = *b;
  a[1] = b[1];
  a[2] = b[2];
  a[3] = b[3];
  return;
}