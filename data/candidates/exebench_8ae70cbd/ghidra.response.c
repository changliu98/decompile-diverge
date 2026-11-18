int foo(int *x)

{
  int *x_local;
  
  *x = *x + 3;
  return *x;
}