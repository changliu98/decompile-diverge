int foo(int *p)

{
  int n;
  int *p_local;
  
  *p = 0xdead;
  return *p;
}