float func0(int a,int b)

{
  double dVar1;
  int temp;
  int digits;
  int b_local;
  int a_local;
  
  digits = 0;
  temp = b;
  if (b == 0) {
    digits = 1;
  }
  else {
    for (; temp != 0; temp = temp / 10) {
      digits = digits + 1;
    }
  }
  dVar1 = pow(DAT_00102008,(double)digits);
  return (float)((double)a + (double)b / dVar1);
}