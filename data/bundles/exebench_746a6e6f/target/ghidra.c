void arrayadd(int *a,int *b)

{
  int i;
  int *b_local;
  int *a_local;
  
  for (i = 0; i < 0x32; i = i + 1) {
    b[i] = a[i] + 5;
  }
  return;
}