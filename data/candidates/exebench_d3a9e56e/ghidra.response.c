void reverseInt(int *p)

{
  int iVar1;
  int temp;
  int i;
  int *p_local;
  
  for (i = 0; i < 5; i = i + 1) {
    iVar1 = p[i];
    p[i] = p[9 - i];
    p[9 - i] = iVar1;
  }
  return;
}