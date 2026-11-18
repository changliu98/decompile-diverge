void f(char *p)

{
  char *p_local;
  
  p[1] = '\x01';
  return;
}