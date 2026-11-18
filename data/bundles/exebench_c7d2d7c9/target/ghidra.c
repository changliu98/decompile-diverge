void passByPointer(int *x)

{
  int *x_local;
  
  *x = 4;
  *x = *x << 2;
  return;
}