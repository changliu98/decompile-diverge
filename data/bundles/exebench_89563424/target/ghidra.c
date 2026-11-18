void f(int *p)

{
  int *p_local;
  
  p[2] = *p;
  p[3] = p[1];
  return;
}