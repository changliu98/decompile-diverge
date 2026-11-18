int func0(int a)

{
  int iVar1;
  int i;
  int a_local;
  
  i = 0;
  while( true ) {
    iVar1 = abs(a);
    if (iVar1 < i * i * i) {
      return 0;
    }
    iVar1 = abs(a);
    if (i * i * i == iVar1) break;
    i = i + 1;
  }
  return 1;
}