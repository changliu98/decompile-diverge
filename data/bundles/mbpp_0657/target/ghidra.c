int func0(int n)

{
  double dVar1;
  int i;
  int fact;
  int n_local;
  
  fact = 1;
  for (i = 2; i <= n; i = i + 1) {
    for (fact = fact * i; fact % 10 == 0; fact = fact / 10) {
    }
  }
  for (; 9 < fact; fact = fact / 10) {
  }
  dVar1 = floor((double)fact);
  return (int)dVar1;
}