int func0(int num1,int num2,int num3)

{
  int lnum;
  int num3_local;
  int num2_local;
  int num1_local;
  
  if ((((num1 < num2) || (lnum = num1, num1 < num3)) && (lnum = num3, num1 <= num2)) &&
     (num3 <= num2)) {
    lnum = num2;
  }
  return lnum;
}