int foo(int *a)

{
  int j;
  int i;
  int *a_local;
  
  j = 0;
  for (i = 0; i < 10; i = i + 1) {
    a[i] = j;
    j = j + 1;
  }
  return i + j;
}