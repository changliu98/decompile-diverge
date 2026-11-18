int divide(int a,int b,int *remainder)

{
  int quot;
  int *remainder_local;
  int b_local;
  int a_local;
  
  *remainder = a % b;
  return a / b;
}