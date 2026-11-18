int take_L_and_F_set_bits(int n){
  int result = n;
  if (n == 1){
    return 0;
  }
  else {
    result = n ^ take_L_and_F_set_bits(n);
  }
  return result;
}