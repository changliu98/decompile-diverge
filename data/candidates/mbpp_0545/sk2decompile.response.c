int func0(int a) {
  if (a == 1) {
    return 0;
  } else {
    return a ^ take_L_and_F_set_bits(a);
  }
}