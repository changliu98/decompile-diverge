int func0(int N)
{
 int i;
 int fac;

 if (N > 9) {
  return 0;
 }

 fac = 1;
 for (i = 1; i <= N; i++) {
  fac = (fac * i) % 100;
 }

 return fac;
}