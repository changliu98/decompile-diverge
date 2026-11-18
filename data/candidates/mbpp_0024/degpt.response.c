/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int func0(int binary)

{
  double dVar1;
  int dec;
  int i;
  int decimal;
  int binary1;
  int binary_local;
  
  decimal = 0;
  i = 0;
  for (binary_local = binary; binary_local != 0; binary_local = binary_local / 10) {
    dVar1 = pow(_DAT_00102008,(double)i);
    decimal = (binary_local % 10) * (int)dVar1 + decimal;
    i = i + 1;
  }
  return decimal;
}