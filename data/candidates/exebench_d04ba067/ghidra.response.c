int itochar(int num,char *strb)

{
  byte bVar1;
  char acStack_138 [256];
  char stra [16];
  uchar j;
  uchar i;
  char *strb_local;
  int num_local;
  
  i = '\0';
  j = '\0';
  num_local = num;
  do {
    bVar1 = i + 1;
    stra[i] = (char)(num_local % 10) + '0';
    num_local = num_local / 10;
    i = bVar1;
  } while (num_local != 0);
  do {
    strb[j] = stra[(int)(((uint)bVar1 - (uint)j) + -1)];
    j = j + 1;
  } while (j < bVar1);
  return (int)j;
}