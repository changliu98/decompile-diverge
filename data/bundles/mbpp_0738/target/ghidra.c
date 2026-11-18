double func0(int n)

{
  double dVar1;
  int n_local;
  undefined8 local_10;
  
  if (n < 0) {
    local_10 = 0.0;
  }
  else {
    local_10 = pow(DAT_00102010,(double)n);
    local_10 = DAT_00102008 / local_10;
    dVar1 = func0(n + -1);
    local_10 = local_10 + dVar1;
  }
  return local_10;
}