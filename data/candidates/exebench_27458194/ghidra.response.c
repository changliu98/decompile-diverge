void foo3(int *a)

{
  int *a_local;
  
  a[3] = a[3] + 10;
  a[4] = a[4] * 0xc;
  return;
}