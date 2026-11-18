double func0(int n)

{
  double dVar1;
  int i;
  double sum;
  int n_local;
  
  sum = 0.0;
  for (i = 1; i <= n; i = i + 1) {
    sum = (double)(i * i * i) + sum;
  }
  dVar1 = round((sum / (double)n) * DAT_00102008);
  return dVar1 / DAT_00102008;
}