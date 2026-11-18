void swap_int(int *pi)

{
  undefined1 uVar1;
  int iVar2;
  uchar *pc;
  uchar t;
  int *pi_local;
  
  iVar2 = *pi;
  *(undefined1 *)pi = *(undefined1 *)((long)pi + 3);
  *(char *)((long)pi + 3) = (char)iVar2;
  uVar1 = *(undefined1 *)((long)pi + 1);
  *(undefined1 *)((long)pi + 1) = *(undefined1 *)((long)pi + 2);
  *(undefined1 *)((long)pi + 2) = uVar1;
  return;
}