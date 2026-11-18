int func0(int N)

{
  int i;
  int fac;
  int N_local;
  undefined4 local_c;
  
  if (N < 10) {
    fac = 1;
    for (i = 1; i <= N; i = i + 1) {
      fac = (fac * i) % 100;
    }
    local_c = fac;
  }
  else {
    local_c = 0;
  }
  return local_c;
}