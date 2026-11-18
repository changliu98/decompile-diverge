void swapIntEndian(int *pInteger)

{
  undefined1 uVar1;
  int iVar2;
  char b;
  char *p;
  int *pInteger_local;
  
  iVar2 = *pInteger;
  *(undefined1 *)pInteger = *(undefined1 *)((long)pInteger + 3);
  *(char *)((long)pInteger + 3) = (char)iVar2;
  uVar1 = *(undefined1 *)((long)pInteger + 1);
  *(undefined1 *)((long)pInteger + 1) = *(undefined1 *)((long)pInteger + 2);
  *(undefined1 *)((long)pInteger + 2) = uVar1;
  return;
}