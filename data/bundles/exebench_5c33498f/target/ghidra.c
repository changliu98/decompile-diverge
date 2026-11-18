int error(int *x)

{
  int *x_local;
  
  *x = *x + 1;
  return *x;
}