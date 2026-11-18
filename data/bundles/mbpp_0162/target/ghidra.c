int func0(int n)

{
  int n_local;
  undefined4 local_c;
  
  if (n < 1) {
    local_c = 0;
  }
  else {
    local_c = func0(n + -2);
    local_c = n + local_c;
  }
  return local_c;
}