int func0(int F) {
 int L;
 if (F == 1)
  L = 0;
 else {
  int F_copy = F;
  L = F ^ take_L_and_F_set_bits(F);
 }
 return L;
}