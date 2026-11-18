void merge(int *a,int *b,int *c)

{
  int k;
  int j;
  int i;
  int *c_local;
  int *b_local;
  int *a_local;
  
  i = 0;
  j = 0;
  k = 0;
  while (i < 6 && j < 6) {
    if (a[i] < b[j]) {
      c[k] = a[i];
      i = i + 1;
    }
    else {
      c[k] = b[j];
      j = j + 1;
    }
    k = k + 1;
  }
  while (i < 6) {
    c[k] = a[i];
    k = k + 1;
    i = i + 1;
  }
  while (j < 6) {
    c[k] = b[j];
    k = k + 1;
    j = j + 1;
  }
  return;
}