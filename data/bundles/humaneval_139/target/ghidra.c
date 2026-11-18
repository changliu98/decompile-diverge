longlong func0(int n)

{
  int i;
  longlong bfact;
  longlong fact;
  int n_local;
  
  fact = 1;
  bfact = 1;
  for (i = 1; i <= n; i = i + 1) {
    fact = fact * i;
    bfact = bfact * fact;
  }
  return bfact;
}