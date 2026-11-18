int gcdEx(int a,int b,int *x,int *y)

{
  int iVar1;
  int t;
  int r;
  int *y_local;
  int *x_local;
  int b_local;
  int a_local;
  undefined4 local_c;
  
  if (b == 0) {
    *x = 1;
    *y = 0;
    local_c = a;
  }
  else {
    local_c = gcdEx(b,a % b,x,y);
    iVar1 = *x;
    *x = *y;
    *y = iVar1 - (a / b) * *y;
  }
  return local_c;
}