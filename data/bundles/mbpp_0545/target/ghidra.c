int func0(int n)

{
  int n_local;
  undefined4 local_c;
  
  if (n == 1) {
    local_c = 0;
  }
  else {
    local_c = take_L_and_F_set_bits(n);
    local_c = n ^ local_c;
  }
  return local_c;
}