int func0(int x,int y)

{
  int iVar1;
  int iVar2;
  double dVar3;
  int i;
  int z;
  int result;
  int n;
  int y_local;
  int x_local;
  
  iVar2 = ngcd(x,y);
  result = 0;
  dVar3 = sqrt((double)iVar2);
  for (i = 1; i <= (int)dVar3; i = i + 1) {
    iVar1 = result;
    if ((iVar2 % i == 0) && (iVar1 = result + 2, i == iVar2 / i)) {
      iVar1 = result + 1;
    }
    result = iVar1;
  }
  return result;
}