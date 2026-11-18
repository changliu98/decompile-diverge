void short_to_string(char *res,unsigned_short s)

{
  byte bVar1;
  char cVar2;
  ushort uVar3;
  unsigned_short r;
  uchar c;
  unsigned_short s_local;
  char *res_local;
  
  bVar1 = (byte)(s / 10000);
  uVar3 = (ushort)bVar1 * 10000;
  *res = bVar1 + 0x30;
  bVar1 = (byte)((int)((uint)s - (uint)uVar3) / 1000);
  uVar3 = uVar3 + (ushort)bVar1 * 1000;
  res[1] = bVar1 + 0x30;
  bVar1 = (byte)((int)((uint)s - (uint)uVar3) / 100);
  uVar3 = uVar3 + (ushort)bVar1 * 100;
  res[2] = bVar1 + 0x30;
  cVar2 = (char)((int)((uint)s - (uint)uVar3) / 10);
  res[3] = cVar2 + '0';
  res[4] = ((char)s - ((char)uVar3 + cVar2 * '\n')) + '0';
  res[5] = '\0';
  return;
}