double func0(int n,int r,double p)

{
  double dVar1;
  double dVar2;
  int i;
  double answer;
  int r0;
  double p_local;
  int r_local;
  int n_local;
  
  r_local = r;
  if (n / 2 < r) {
    r_local = n - r;
  }
  answer = DAT_00102008;
  for (i = 1; i <= r_local; i = i + 1) {
    answer = ((double)((n - r_local) + i) * answer) / (double)i;
  }
  dVar1 = pow(p,(double)r);
  dVar2 = pow(DAT_00102008 - p,(double)(n - r));
  return answer * dVar1 * dVar2;
}