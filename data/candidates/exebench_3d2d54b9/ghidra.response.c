int foo(int p,int *q)

{
  int *q_local;
  int p_local;
  
  if (p == 9) {
    q[1] = 0;
  }
  else {
    *q = 0;
  }
  return 3;
}