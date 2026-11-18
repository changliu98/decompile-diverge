void foo(long n,long *p,long *q)

{
  long i;
  long *q_local;
  long *p_local;
  long n_local;
  
  if (0 < n) {
    foo(n / 2,p,q);
    for (i = 1; i <= n; i = i + 1) {
      *p = *q + *p;
    }
  }
  return;
}