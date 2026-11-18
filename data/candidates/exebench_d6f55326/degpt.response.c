void swap_long(long *pi)

{
  undefined1 uVar1;
  long lVar2;
  uchar *pc;
  uchar t;
  long *pi_local;
  
  lVar2 = *pi;
  *(undefined1 *)pi = *(undefined1 *)((long)pi + 3);
  *(char *)((long)pi + 3) = (char)lVar2;
  uVar1 = *(undefined1 *)((long)pi + 1);
  *(undefined1 *)((long)pi + 1) = *(undefined1 *)((long)pi + 2);
  *(undefined1 *)((long)pi + 2) = uVar1;
  return;
}