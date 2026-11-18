void shiftarray(int *a)

{
  int i;
  int *a_local;
  
  for (i = 0; i < 9; i = i + 1) {
    a[i] = a[(long)i + 1];
  }
  a[9] = -1;
  return;
}